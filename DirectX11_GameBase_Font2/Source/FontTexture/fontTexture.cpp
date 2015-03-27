//==============================================================================
// File		FontTexture.cpp
// Comment	DirectX�t�H���g1�����e�N�X�`����������
// Author	TOMOHIRO KOUNO
// Create	2015�N3��13��
//==============================================================================

//------------------------------------------------------------------------------
// �C���N���[�h
//------------------------------------------------------------------------------
#include <Shlwapi.h>
#include "fontTexture.h"
#include "system/SystemManager.h"

//------------------------------------------------------------------------------
// static �萔��`
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
			SafeRelease(m_Datas[i].m_tex2D);
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
			TEXT("MS�S�V�b�N")
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

	// �f�o�C�X�Ƀt�H���g���������Ȃ���GetGlyphOutline�֐��̓G���[�ƂȂ�
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
	//�N���X�ɑ΂��Ĉ�x�����K�v���𐶐�
	CreateHDCAndFontOnce(fontsize);
	
	// �����R�[�h�擾
	UINT code = 0;
	#if _UNICODE
	// unicode�̏ꍇ�A�����R�[�h�͒P���Ƀ��C�h������UINT�ϊ��ł�
		code = (UINT)*c;
	#else
	// �}���`�o�C�g�����̏ꍇ�A
	// 1�o�C�g�����̃R�[�h��1�o�C�g�ڂ�UINT�ϊ��A
	// 2�o�C�g�����̃R�[�h��[�擱�R�[�h]*256 + [�����R�[�h]�ł�
	if(IsDBCSLeadByte(*c))
		code = (BYTE)c[0]<<8 | (BYTE)c[1];
	else
		code = c[0];
	#endif

	//���O�o�^���ꂽ�����f�[�^���邩����
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

	//���O�f�[�^����������A���̃e�N�X�`����Ԃ��΂悢
	if (preData)
	{
		m_Datas[hitID].m_charCode = (UINT)*c;
		return m_Datas[hitID].m_pTextureResource;
	}

	//���߂Č��镶����Ȃ�r�b�g�}�b�v�t�H���g��p�ӂ���
	m_Datas[hitID].m_charCode = (UINT)*c;

	// �t�H���g�r�b�g�}�b�v�擾
	static TEXTMETRIC TM;
	static GLYPHMETRICS GM;
	static const MAT2 Mat = { { 0, 1 }, { 0, 0 }, { 0, 0 }, { 0, 1 } };
	GetTextMetrics(m_HDC, &TM);
	
	DWORD size = GetGlyphOutline(m_HDC, code, GGO_GRAY4_BITMAP, &GM, 0, NULL, &Mat);
	BYTE* ptr = new BYTE[ size ];
	GetGlyphOutline(m_HDC, code, GGO_GRAY4_BITMAP, &GM, size, ptr, &Mat);

	//--------------------------------
	// CPU�ŏ������݂��ł���e�N�X�`�����쐬
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

	// �����ŏ�������
	BYTE* pBits = (BYTE*)hMappedResource.pData;

	// �t�H���g���̏�������
	// iOfs_x, iOfs_y : �����o���ʒu(����)
	// iBmp_w, iBmp_h : �t�H���g�r�b�g�}�b�v�̕���
	// Level : ���l�̒i�K (GGO_GRAY4_BITMAP�Ȃ̂�17�i�K)
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

	//�������܂ꂽ�e�N�X�`���̏���n����`���ɕύX
	D3D11_TEXTURE2D_DESC texDesc;
	tex2D->GetDesc(&texDesc);

	// ShaderResourceView�̏����쐬����
	D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
	ZeroMemory(&srvDesc, sizeof(srvDesc));
	srvDesc.Format						= texDesc.Format;
	srvDesc.ViewDimension				= D3D11_SRV_DIMENSION_TEXTURE2D;
	srvDesc.Texture2D.MostDetailedMip	= 0;
	srvDesc.Texture2D.MipLevels			= texDesc.MipLevels;
	hr = pDevice->CreateShaderResourceView(tex2D, &srvDesc, &m_Datas[hitID].m_pTextureResource);
	
	m_Datas[hitID].m_tex2D = tex2D;
	//SafeRelease(tex2D);
	SafeDeleteArray(ptr);

	return m_Datas[hitID].m_pTextureResource;
}
