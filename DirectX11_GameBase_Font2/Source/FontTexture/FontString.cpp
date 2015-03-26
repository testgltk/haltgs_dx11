//==============================================================================
// File		FontString.cpp
// Comment	DirectXフォント文字列描画
// Author	TOMOHIRO KOUNO
// Create	2015年3月15日
//==============================================================================

//------------------------------------------------------------------------------
// インクルード
//------------------------------------------------------------------------------
#include "FontString.h"
#include "FontTexture.h"
#include "Sprite/Sprite.h"

CFontString::CFontString()
:m_UseTextNum(0)
{
	m_pFontTextures = new FontTexture *[MAX_FONT_DISP_SIZE];
	m_pSprites		= new CSprite *[MAX_FONT_DISP_SIZE];
	for (int i = 0; i < MAX_FONT_DISP_SIZE; i++)
	{
		m_pSprites[i]		= new CSprite();
		m_pFontTextures[i]	= new FontTexture();
		m_pSprites[i]->SetTexture(nullptr);
		m_pSprites[i]->SetPosition(XMFLOAT2(0,0));
		m_pSprites[i]->SetColor(XMFLOAT4(0, 0, 0, 0));
	}
}

CFontString::~CFontString(void)
{
	for (int i = 0; i < MAX_FONT_DISP_SIZE; i++)
	{
		m_pSprites[i]->SetTextureNone();
		SafeDelete(m_pFontTextures[i]);
		SafeDelete(m_pSprites[i]);
	}
	SafeDeleteArray(m_pFontTextures);
	SafeDeleteArray(m_pSprites);
}

void CFontString::Update(void)
{
	m_Position.x =
	m_Position.y =
	m_UseTextNum = 0;
	m_Text = L"";
	SetColor(XMFLOAT4(1, 1, 1, 1));
}

void CFontString::Draw(void)
{
	for (int i = 0; i < m_UseTextNum; i++)
	{
		m_pSprites[i]->SetTextureUnsafeFont(m_pFontTextures[i]->Create(&m_Text[i], 256));
		m_pSprites[i]->Draw();
	}
}

void CFontString::printfString(const TCHAR* format, ...) {
	
	//改行用に開始時座標を取得
	XMFLOAT2 StartPos = m_Position;

	static TCHAR strBuffer_g[BUFFER_MAX];
	ZeroMemory(&strBuffer_g, sizeof(strBuffer_g));
	va_list args;
	va_start(args, format);

	//一度に転送される文字数が多くてもエラー
#if _DEBUG
	int len = _vsctprintf(format, args);
	if (len >= BUFFER_MAX)
		_ASSERT(0);
#endif

	_vstprintf(strBuffer_g, format, args);

	int nSize = _tcslen(strBuffer_g);
	int nCount = 0;

	//ここでの文字数とは文字の種類数でなく、画面に表示される文字数を表します。
	MYASSERT(((m_UseTextNum + nSize) < MAX_FONT_DISP_SIZE), " CFontString::printfString is BUFFER OVERFLOW MAX = %d", MAX_FONT_DISP_SIZE);

	for (int i = m_UseTextNum; i < m_UseTextNum + nSize; i++)
	{
		m_pSprites[i]->SetPosition(m_Position);

		//改行コードのチェック
		if (strBuffer_g[nCount] == '\n')
		{
			//改行の際は次の文字へスキップ
			//テクスチャ的にはαで対応
			m_pSprites[i]->SetColor(XMFLOAT4(0, 0, 0, 0));
			m_Position.x = StartPos.x;
			m_Position.y += OFFSET_Y;
		}
		else
		{
			m_pSprites[i]->SetColor(m_Color);
			m_Position.x += OFFSET_X;
		}
		nCount++;
	}

	m_UseTextNum += nSize;
	m_Text.append(strBuffer_g);
}

//TO DO 本来なら上記関数と重複コードが多く１つにまとめたいが
//文字列フォーマットの性質上厄介な事項があり保留。(多引数関数の引数をその多引数にする)
//時間あるときに対応したい
void CFontString::printfString(const XMFLOAT2& pos, const TCHAR* format, ...)
{
	m_Position = pos;

	static TCHAR strBuffer_g[BUFFER_MAX];
	ZeroMemory(&strBuffer_g, sizeof(strBuffer_g));
	va_list args;
	va_start(args, format);

	//一度に転送される文字数が多くてもエラー
	#if _DEBUG
		int len = _vsctprintf(format, args);
		if (len >= BUFFER_MAX)
			_ASSERT(0);
	#endif

	_vstprintf(strBuffer_g, format, args);

	int nSize  = _tcslen(strBuffer_g);
	int nCount = 0;

	//ここでの文字数とは文字の種類数でなく、画面に表示される文字数を表します。
	MYASSERT(((m_UseTextNum + nSize) < MAX_FONT_DISP_SIZE), " CFontString::printfString is BUFFER OVERFLOW MAX = %d", MAX_FONT_DISP_SIZE);

	for (int i = m_UseTextNum; i < m_UseTextNum + nSize; i++)
	{
		m_pSprites[i]->SetPosition(m_Position);

		//改行コードのチェック
		if (strBuffer_g[nCount] == '\n')
		{
			//改行の際は次の文字へスキップ
			//テクスチャ的にはαで対応
			m_pSprites[i]->SetColor(XMFLOAT4(0, 0, 0, 0));
			m_Position.x = pos.x;
			m_Position.y += OFFSET_Y;
		}
		else
		{
			m_pSprites[i]->SetColor(m_Color);
			m_Position.x += OFFSET_X;
		}
		nCount++;
	}

	m_UseTextNum += nSize;
	m_Text.append(strBuffer_g);
}

void CFontString::SetColor(const XMFLOAT4& color)
{
	m_Color = color;
}