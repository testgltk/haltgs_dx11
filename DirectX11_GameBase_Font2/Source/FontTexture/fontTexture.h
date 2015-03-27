//==============================================================================
// File		FontTexture.h
// Comment	DirectX�t�H���g1�����e�N�X�`����������
// Author	TOMOHIRO KOUNO
// Create	2015�N3��13��
//==============================================================================

//------------------------------------------------------------------------------
// �C���N���[�h�K�[�h
//------------------------------------------------------------------------------
#pragma once
#ifndef _FONTTEXTURE_H_
#define _FONTTEXTURE_H_

//------------------------------------------------------------------------------
// �C���N���[�h
//------------------------------------------------------------------------------
#include <d3dx11.h>

/**
* @brief DirectX11 �t�H���g1�����e�N�X�`�������N���X
*/
class FontTexture
{
public:

	static const int MAX_CHAR_SIZE = 512; ///> �t�H���g�e�N�X�`���Ɋi�[����ő�F��������

	typedef struct DATA_TAG
	{
		ID3D11ShaderResourceView* m_pTextureResource;	///> �Ή�����e�N�X�`�����
		UINT m_charCode;								///> �i�[������
		ID3D11Texture2D* m_tex2D;
	} DATA;

	/**
	* @brief	Constructor
	* @param	void
	* @return	void
	*/
	FontTexture();

	/**
	* @brief Destructor
	*/
	~FontTexture();

	/**
	*	��������ɑΉ����镶���e�N�X�`���̍쐬(�d�����͓����ŉ�����܂�)
	*	@param	�����R�[�h
	*	@param	�����̃T�C�Y
	*	@return	DirectX11�ɑΉ������V�F�[�_�ɑ��邽�߂̃e�N�X�`���|�C���^
	*/
	ID3D11ShaderResourceView* Create(TCHAR* c, int fontSize);

private:
	void CreateHDCAndFontOnce(int fontSize);///> ��x�����t�H���g��HDC�R���e�L�X�g��p��
	static LOGFONT	m_LogFont;				///> �t�H���g�p�̃f�[�^�\����
	static HFONT	m_HFont;				///> �`��p�t�H���g�n���h��
	static HFONT	m_OldFont;				///> �����p�̃t�H���g�n���h��
	static HDC		m_HDC;					///> Windows�p�̕`��n���h��
	static bool		m_Once;					///> �N���X��񏈗��p�t���O
	static DATA		m_Datas[MAX_CHAR_SIZE];			///> �i�[���\����
};
#endif
// End of File _FONTTEXTURE_H_