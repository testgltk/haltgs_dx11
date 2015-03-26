//==============================================================================
// File		FontString.cpp
// Comment	DirectX�t�H���g������`��
// Author	TOMOHIRO KOUNO
// Create	2015�N3��15��
//==============================================================================

//------------------------------------------------------------------------------
// �C���N���[�h
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
	
	//���s�p�ɊJ�n�����W���擾
	XMFLOAT2 StartPos = m_Position;

	static TCHAR strBuffer_g[BUFFER_MAX];
	ZeroMemory(&strBuffer_g, sizeof(strBuffer_g));
	va_list args;
	va_start(args, format);

	//��x�ɓ]������镶�����������Ă��G���[
#if _DEBUG
	int len = _vsctprintf(format, args);
	if (len >= BUFFER_MAX)
		_ASSERT(0);
#endif

	_vstprintf(strBuffer_g, format, args);

	int nSize = _tcslen(strBuffer_g);
	int nCount = 0;

	//�����ł̕������Ƃ͕����̎�ސ��łȂ��A��ʂɕ\������镶������\���܂��B
	MYASSERT(((m_UseTextNum + nSize) < MAX_FONT_DISP_SIZE), " CFontString::printfString is BUFFER OVERFLOW MAX = %d", MAX_FONT_DISP_SIZE);

	for (int i = m_UseTextNum; i < m_UseTextNum + nSize; i++)
	{
		m_pSprites[i]->SetPosition(m_Position);

		//���s�R�[�h�̃`�F�b�N
		if (strBuffer_g[nCount] == '\n')
		{
			//���s�̍ۂ͎��̕����փX�L�b�v
			//�e�N�X�`���I�ɂ̓��őΉ�
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

//TO DO �{���Ȃ��L�֐��Əd���R�[�h�������P�ɂ܂Ƃ߂�����
//������t�H�[�}�b�g�̐�������Ȏ���������ۗ��B(�������֐��̈��������̑������ɂ���)
//���Ԃ���Ƃ��ɑΉ�������
void CFontString::printfString(const XMFLOAT2& pos, const TCHAR* format, ...)
{
	m_Position = pos;

	static TCHAR strBuffer_g[BUFFER_MAX];
	ZeroMemory(&strBuffer_g, sizeof(strBuffer_g));
	va_list args;
	va_start(args, format);

	//��x�ɓ]������镶�����������Ă��G���[
	#if _DEBUG
		int len = _vsctprintf(format, args);
		if (len >= BUFFER_MAX)
			_ASSERT(0);
	#endif

	_vstprintf(strBuffer_g, format, args);

	int nSize  = _tcslen(strBuffer_g);
	int nCount = 0;

	//�����ł̕������Ƃ͕����̎�ސ��łȂ��A��ʂɕ\������镶������\���܂��B
	MYASSERT(((m_UseTextNum + nSize) < MAX_FONT_DISP_SIZE), " CFontString::printfString is BUFFER OVERFLOW MAX = %d", MAX_FONT_DISP_SIZE);

	for (int i = m_UseTextNum; i < m_UseTextNum + nSize; i++)
	{
		m_pSprites[i]->SetPosition(m_Position);

		//���s�R�[�h�̃`�F�b�N
		if (strBuffer_g[nCount] == '\n')
		{
			//���s�̍ۂ͎��̕����փX�L�b�v
			//�e�N�X�`���I�ɂ̓��őΉ�
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