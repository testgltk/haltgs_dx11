//==============================================================================
// File		FontString.h
// Comment	DirectX�t�H���g������`��
// Author	TOMOHIRO KOUNO
// Create	2015�N3��15��
//==============================================================================

//==============================================================================
// ���ӓ_
// DirectX11�ł̎��R�ȃt�H���g�쐬�����ɂ͑�K�͂ȍH�����K�v�ɂȂ邽�߁A
// ���݂͗��p���@�ɐ������������邱�Ƃɂ��܂����B
// ��̓I�ɂ͈ȉ��Ɏ��������ł��B
// [1]:��{�I�ɂ̓f�o�b�O�p�r�ł��B�K���X�V���Ă�ł��當�����ǉ����Ă��������B
// [2]:������̍ė��p�ɂ��L���b�V����DirectX11�ł͋�������邽��
//     �e�N�X�`���}�l�[�W���Ȃǂɔ�ˑ��ȃL���b�V���@�\��t�^���Ă��܂��B
// [3]:���݂�@�}�[�N���������p�̃}�[�N�ɗ��p���Ă܂��B
//==============================================================================

//------------------------------------------------------------------------------
// �C���N���[�h�K�[�h
//------------------------------------------------------------------------------
#pragma once
#ifndef _FONTSTRING_H_
#define _FONTSTRING_H_

//------------------------------------------------------------------------------
// �C���N���[�h
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// �O���錾
//------------------------------------------------------------------------------
class FontTexture;
class CSprite;

/**
* @brief DirectX11 ������`��N���X
*/
class CFontString
{
public:
	static const u16 MAX_FONT_DISP_SIZE = 255;		///> ������̕\�����E��
	static const u8 OFFSET_X			= 32;		///> �����ԊuX
	static const u8 OFFSET_Y			= 32;		///> �����ԊuY
	static const u16 BUFFER_MAX			= 1024;		///> �������͗p�̃o�b�t�@���E

	/**
	* @brief	Constructor
	* @param	void
	* @return	void
	*/
	CFontString(void);

	/**
	* @brief Destructor
	*/
	~CFontString(void);

	/**
	*	�X�V
	*	@param	void
	*	@return	void
	*/
	void Update(void);

	/**
	*	�`��
	*	@param	void
	*	@return	void
	*/
	void Draw(void);

	/**
	*	�����̕\��
	*	@param	������t�H�[�}�b�g
	*	@return	void
	*/
	void printfString(const TCHAR* format, ...);
	void printfString(const XMFLOAT2& pos,const TCHAR* format, ...);

	/**
	*	���݂̕`��F��ύX����
	*	@param	void
	*	@return	void
	*/
	void SetColor(const XMFLOAT4& color);

private:
	TString			m_Text;											///> Unicode �Ή��X�g�����O
	FontTexture**	m_pFontTextures		= nullptr;					///> �e�N�X�`���p�f�[�^�|�C���^�z��
	CSprite**		m_pSprites			= nullptr;					///> �`��p2D�|���S���|�C���^�z��
	int				m_UseTextNum		= 0;						///> ���ݕ`�敶����
	XMFLOAT2		m_Position			= XMFLOAT2(0, 0);			///> ���ݕ`��ʒu
	XMFLOAT4		m_Color				= XMFLOAT4(1, 1, 1, 1);		///> ���ݕ`��F
};
#endif
//End of File _FONTSTRING_H_