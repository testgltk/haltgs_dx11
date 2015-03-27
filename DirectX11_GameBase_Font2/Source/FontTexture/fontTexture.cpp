//==============================================================================
// File		FontTexture.cpp
// Comment	DirectXフォント1文字テクスチャ生成処理
// Author	TOMOHIRO KOUNO
// Create	2015年3月13日
//==============================================================================

//------------------------------------------------------------------------------
// インクルード
//------------------------------------------------------------------------------
#include <Shlwapi.h>
#include "fontTexture.h"
#include "system/SystemManager.h"

//------------------------------------------------------------------------------
// static 定数定義
//------------------------------------------------------------------------------
LOGFONT			FontTexture::m_LogFont	= { NULL };
HFONT			FontTexture::m_HFont	= NULL;
HFONT			FontTexture::m_OldFont	= NULL;
HDC				FontTexture::m_HDC		= NULL;
bool			FontTexture::m_Once		= false;

FontTexture::DATA FontTexture::m_Datas[FontTexture::MAX_CHAR_SIZE] = { NULL };

FontTexture::FontTexture()
{
	if (!m_Once)
	{
		for (int i = 0; i < MAX_CHAR_SIZE; i++)
		{
			m_Datas[i].m_charCode = '@';
		}
		m_Once = true;
	}
}

FontTexture::~FontTexture()
{
	SelectObject(m_HDC, m_OldFont);
	DeleteObject(m_HFont);
	ReleaseDC(NULL, m_HDC);

	if (m_Once)
	{
		for (int i = 0; i < MAX_CHAR_SIZE; i++)
		{
			SafeRelease(m_Datas[i].m_pTextureResource);
		}

		m_Once = false;
	}
}

void FontTexture::CreateHDCAndFontOnce(int fontsize)
{
	if (m_LogFont.lfHeight == 0)
	{
		m_LogFont = {
			fontsize,
			0,
			0,
			0,
			0,
			0,
			0,
			0,
			SHIFTJIS_CHARSET,
			OUT_TT_ONLY_PRECIS,
			CLIP_DEFAULT_PRECIS,
			PROOF_QUALITY,
			FIXED_PITCH | FF_MODERN,
			TEXT("MSゴシック")
		};
	}

	HRESULT hr;

	if (!m_HFont)
	{
		m_HFont = CreateFontIndirect(&m_LogFont);
		if (!m_HFont)
		{
			//Failed!
		}
	}

	// デバイスにフォントを持たせないとGetGlyphOutline関数はエラーとなる
	if (!m_HDC)
	{
		m_HDC = GetDC(NULL);
	}

	if (!m_OldFont)
	{
		m_OldFont = (HFONT)SelectObject(m_HDC, m_HFont);
	}
}

ID3D11ShaderResourceView* FontTexture::Create(TCHAR* c, int fontsize)
{
	//クラスに対して一度だけ必要情報を生成
	CreateHDCAndFontOnce(fontsize);
	
	// 文字コード取得
	UINT code = 0;
	#if _UNICODE
	// unicodeの場合、文字コードは単純にワイド文字のUINT変換です
		code = (UINT)*c;
	#else
	// マルチバイト文字の場合、
	// 1バイト文字のコードは1バイト目のUINT変換、
	// 2バイト文字のコードは[先導コード]*256 + [文字コード]です
	if(IsDBCSLeadByte(*c))
		code = (BYTE)c[0]<<8 | (BYTE)c[1];
	else
		code = c[0];
	#endif

	//事前登録された文字データあるか判定
	bool preData = false;
	int hitID = 0;
	for (int n = 0; n < MAX_CHAR_SIZE; n++)
	{
		if (m_Datas[n].m_charCode == (UINT)*c)
		{
			preData = true;
			hitID = n;
			break;
		}
		else if((char)(m_Datas[n].m_charCode) == '@')
		{
			hitID = n;
			break;
		}
	}

	//事前データがあったら、そのテクスチャを返せばよい
	if (preData)
	{
		m_Datas[hitID].m_charCode = (UINT)*c;
		return m_Datas[hitID].m_pTextureResource;
	}

	//初めて見る文字列ならビットマップフォントを用意する
	m_Datas[hitID].m_charCode = (UINT)*c;

	// フォントビットマップ取得
	static TEXTMETRIC TM;
	static GLYPHMETRICS GM;
	static const MAT2 Mat = { { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 1 } };
	GetTextMetrics(m_HDC, &TM);
	
	DWORD size = GetGlyphOutline(m_HDC, code, GGO_GRAY4_BITMAP, &GM, 0, NULL, &Mat);
	BYTE* ptr = new BYTE[ size ];
	GetGlyphOutline(m_HDC, code, GGO_GRAY4_BITMAP, &GM, size, ptr, &Mat);

	//--------------------------------
	// CPUで書き込みができるテクスチャを作成
	//--------------------------------
	D3D11_TEXTURE2D_DESC desc;
	memset( &desc, 0, sizeof( desc ) );
	desc.Width				= GM.gmCellIncX;
	desc.Height				= TM.tmHeight;
	desc.MipLevels			= 1;
	desc.ArraySize			= 1;
	desc.Format				= DXGI_FORMAT_R8G8B8A8_UNORM;	// RGBA(255,255,255,255)
	desc.SampleDesc.Count	= 1;
	desc.Usage				= D3D11_USAGE_DYNAMIC;
	desc.BindFlags			= D3D11_BIND_SHADER_RESOURCE;
	desc.CPUAccessFlags		= D3D11_CPU_ACCESS_WRITE;

	ID3D11Texture2D* tex2D = nullptr;

	ID3D11Device* pDevice = GETDEVICE;
	ID3D11DeviceContext* pDeviceContext = GETDEVICECONTEXT;

	HRESULT hr = pDevice->CreateTexture2D(&desc, 0, &tex2D);
		
	D3D11_MAPPED_SUBRESOURCE hMappedResource;
	hr = pDeviceContext->Map(tex2D,0,D3D11_MAP_WRITE_DISCARD,0,&hMappedResource );

	// ここで書き込む
	BYTE* pBits = (BYTE*)hMappedResource.pData;

	// フォント情報の書き込み
	// iOfs_x, iOfs_y : 書き出し位置(左上)
	// iBmp_w, iBmp_h : フォントビットマップの幅高
	// Level : α値の段階 (GGO_GRAY4_BITMAPなので17段階)
	int iOfs_x = GM.gmptGlyphOrigin.x;
	int iOfs_y = TM.tmAscent - GM.gmptGlyphOrigin.y;
	int iBmp_w = GM.gmBlackBoxX + ( 4 - ( GM.gmBlackBoxX % 4 ) ) % 4 ;
	int iBmp_h = GM.gmBlackBoxY;
	int Level = 17;
	int x, y;
	DWORD Alpha, Color;
	memset( pBits, 0, hMappedResource.RowPitch * TM.tmHeight );
	for( y = iOfs_y; y < iOfs_y + iBmp_h; y++ )
	{
		for( x = iOfs_x; x < iOfs_x + iBmp_w; x++)
		{
			Alpha = ( 255 * ptr[ x - iOfs_x + iBmp_w * ( y - iOfs_y ) ] ) / ( Level - 1 );
			Color = 0x00ffffff | ( Alpha << 24 );
			memcpy( (BYTE*)pBits + hMappedResource.RowPitch * y + 4 * x, &Color, sizeof(DWORD) );
		}
	}

	pDeviceContext->Unmap(tex2D, 0);

	//書き込まれたテクスチャの情報を渡せる形式に変更
	D3D11_TEXTURE2D_DESC texDesc;
	tex2D->GetDesc(&texDesc);

	// ShaderResourceViewの情報を作成する
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format						= texDesc.Format;
	srvDesc.ViewDimension				= D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip	= 0;
	srvDesc.Texture2D.MipLevels			= texDesc.MipLevels;
	hr = pDevice->CreateShaderResourceView(tex2D, &srvDesc, &m_Datas[hitID].m_pTextureResource);
	
	//SafeRelease(tex2D);
	SafeDeleteArray(ptr);

	return m_Datas[hitID].m_pTextureResource;
}
