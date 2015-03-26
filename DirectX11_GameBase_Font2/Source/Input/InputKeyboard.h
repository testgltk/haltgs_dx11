//==============================================================================
// File		InputKeyboard.h
// Comment	�L�[�{�[�h���̓N���X
// Author	TOMOHIRO KOUNO
// Create	2014�N6��27��
//==============================================================================

//------------------------------------------------------------------------------
//	�C���N���[�h�K�[�h
//------------------------------------------------------------------------------
#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_

//------------------------------------------------------------------------------
//	�C���N���[�h
//------------------------------------------------------------------------------
#include "Input/Input.h"
#include "Common/Common.h"
/**
* @brief �L�[�{�[�h���̓N���X
*/
class CInputKeyboard : public CInput
{
public:

	enum {KEY_ARRAY_MAX = 256};	///> �L�[�z��̍ő吔
	enum {REPEAT_TIME = 20};	///> �L�[���s�[�g�Ƃ݂Ȃ�����
	/**
	* @brief Constructor
	* @param	void
	* @return	void
	*/
	CInputKeyboard(void);

	/**
	* @brief Destructor
	*/
	~CInputKeyboard(void);

	/**
	*	Init Input Device
	*	@param	hInst �n���h���C���X�^���X
	*	@param	hWnd  �n���h���E�B���h�E
	*	@return	�������ɐ���������?
	*/
	virtual HRESULT Initialize(HINSTANCE hInst, HWND hWnd);

	/**
	*	Uninitilaize Input Device
	*	@param	void
	*	@return	void
	*/
	virtual void Uninitialize(void);

	/**
	*	Update Input Device Pure Fucntion
	*	@param	void
	*	@return	void
	*/
	void Update(void);

	/**
	*	�L�[�����������Ă邩�H
	*	@param	nKey �L�[�ԍ�
	*	@return	BOOL ������Ă邩�ǂ���
	*/
	BOOL IsKeyPress		(int nKey);

	/**
	*	�L�[���������u�Ԃ��H
	*	@param	nKey	�L�[�ԍ�
	*	@param	bIgnore	�f�����Ƀg���K�[����
	*			���[�h�f�[�^�ɂ��Ă���̂��ꎞ�I�ɖ�������
	*			(�f�����ɃX�L�b�v���s���ۂɂ͕K�v)
	*	@return	BOOL �������u�Ԃ��ǂ���
	*/
	BOOL IsKeyTrigger	(int nKey,bool bIgnore = false);

	/**
	*	�L�[�𗣂����u�Ԃ��H
	*	@param	nKey �L�[�ԍ�
	*	@return	BOOL �������u�Ԃ��ǂ���
	*/
	BOOL IsKeyRelease	(int nKey);

	/**
	*	�L�[�𗣂����u�Ԃ܂����������Ă邩�H
	*	@param	nKey �L�[�ԍ�
	*	@return	BOOL �������u�Ԃ܂����������Ă邩�ǂ���
	*/
	BOOL IsKeyRepeat	(int nKey);

	/**
	*	�L�[���͂̏���
	*	@param	nKey �L�[�ԍ�
	*	@return	void
	*/
	void FlushKeyTrigger(int nKey);

	/**
	*	�L�[���͔z�񏉊���
	*	@param	void
	*	@return	void
	*/
	void ClearState(void);

	/**
	*	�㉺�ɊY������L�[�������ꂽ
	*	@param	void
	*	@return	��L�[ : 1 ���L�[ -1 ������0
	*/
	float GetAxisVertical(void);

	/**
	*	���E�ɊY������L�[�������ꂽ
	*	@param	void
	*	@return	�E�L�[ : 1 ���L�[ -1 ������0
	*/
	float GetAxisHorizontal(void);

	/**
	*	�L�[�f�[�^�ۑ��J�n
	*	@param	void
	*	@return	TRUE : �ۑ��J�n����
	*	@return	FALSE: �ۑ��J�n���s
	*/
	bool StartSaveKeyState(void);

	/**
	*	�L�[�f�[�^�ۑ��I��
	*	@param	void
	*	@return	TRUE : �ۑ��I������
	*	@return	FALSE: �ۑ��I�����s
	*/
	bool EndSaveKeyState(void);

	/**
	*	�L�[�f�[�^�ǂݍ��݊J�n
	*	@param	void
	*	@return	TRUE : �ǂݍ��݊J�n����
	*	@return	FALSE: �ǂݍ��݊J�n���s
	*/
	bool StartLoadKeyState(void);

	/**
	*	�L�[�f�[�^�ǂݍ��ݏI��
	*	@param	void
	*	@return	TRUE : �ǂݍ��ݏI������
	*	@return	FALSE: �ǂݍ��ݏI�����s
	*/
	bool EndLoadKeyState(void);

private:
	BYTE m_aKeyState			[KEY_ARRAY_MAX];	///> �L�[�{�[�h�̏�Ԃ��󂯎�郏�[�N
	BYTE m_aKeyStateTrigger		[KEY_ARRAY_MAX];	///> �g���K�[���[�N
	BYTE m_aKeyStateRelease		[KEY_ARRAY_MAX];	///> �����[�X���[�N
	BYTE m_aKeyStateRepeat		[KEY_ARRAY_MAX];	///> ���s�[�g���[�N
	int	 m_aKeyStateRepeatCnt	[KEY_ARRAY_MAX];	///> ���s�[�g�J�E���^

	// �L�[���̃Z�[�u�E���[�h���
	typedef enum
	{
		KEYSTATE_MODE_NONE = 0,						///> �������Ă��Ȃ�
		KEYSTATE_MODE_SAVE,							///> �L�[���Z�[�u��
		KEYSTATE_MODE_LOAD,							///> �L�[��񃍁[�h��
	} KEYSTATE_MODE;


	//TO DEMO STATE
	static const int SAVE_FRAME = 3600;			///> �L�[�X�e�[�g��ۑ�����t���[����
	BYTE*			m_pFileKeyState;			///> �Z�[�u�E���[�h�p�L�[��񃏁[�N
	BYTE*			m_pFileKeyStateTrigger;		///> �Z�[�u�E���[�h�p�L�[�g���K�[���[�N
	BYTE*			m_pFileKeyStateRelease;		///> �Z�[�u�E���[�h�p�L�[�����[�X���[�N
	BYTE*			m_pFileKeyStateRepeat;		///> �Z�[�u�E���[�h�p�L�[���s�[�g���[�N
	int				m_cntFrame;					///> �t�@�C���Z�[�u�E���[�h���̃t���[���J�E���^
	KEYSTATE_MODE	m_keyStateMode;				///> �L�[���̃Z�[�u�E���[�h���

	/**
	*	�L�[�f�[�^�ۑ�����
	*	@param	void
	*	@return	void
	*/
	void SaveKeyState(void);

	/**
	*	�L�[�f�[�^�ǂݍ��ݏ���
	*	@param	void
	*	@return	void
	*/
	void LoadKeyState(void);
};
#endif
//End of File _INPUTKEYBOARD_H_