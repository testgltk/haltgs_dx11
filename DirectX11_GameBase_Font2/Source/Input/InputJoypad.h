//==============================================================================
// File		InputJoypad.h
// Comment	�W���C�p�b�h���̓N���X
// Author	TOMOHIRO KOUNO
// Create	2014�N6��27��
//==============================================================================

//------------------------------------------------------------------------------
//	�C���N���[�h�K�[�h
//------------------------------------------------------------------------------
#ifndef _INPUTJOYPAD_H_
#define _INPUTJOYPAD_H_

//------------------------------------------------------------------------------
//	�C���N���[�h
//------------------------------------------------------------------------------
#include "Input/Input.h"
#include "Common/Common.h"
/**
* @brief �W���C�p�b�h���̓N���X
*/
class CInputJoypad : CInput
{
public:
	/**
	* @brief Constructor
	* @param	void
	* @return	void
	*/
	CInputJoypad(void);

	/**
	* @brief Destructor
	*/
	~CInputJoypad(void);

	/**
	*	Init JoyPad Device
	*	@param	hInst �n���h���C���X�^���X
	*	@param	hWnd  �n���h���E�B���h�E
	*	@return	�������ɐ���������?
	*/
	HRESULT Initialize(HINSTANCE hInst, HWND hWnd);

	/**
	*	Uninitilaize JoyPad Device
	*	@param	void
	*	@return	void
	*/
	void Uninitialize(void);

	/**
	*	Update JoyPad Device Pure Fucntion
	*	@param	void
	*	@return	void
	*/
	void Update(void);

	// �L�[�̎��
	typedef enum
	{
		KEY_LEFT = 0,
		KEY_RIGHT,
		KEY_UP,
		KEY_DOWN,
		KEY_JUMP,
		KEY_SHOT,
		KEY_TURN_LEFT,
		KEY_TURN_RIGHT,
		KEY_TURN_UP,
		KEY_TURN_DOWN,
		KEY_START,
		KEY_SELECT,
		KEY_MAX
	} KEY;

	/**
	*	�L�[�����������Ă邩�H
	*	@param	nKey �L�[�ԍ�
	*	@return	bool ������Ă邩�ǂ���
	*/
	bool IsKeyPress(KEY key);

	/**
	*	�L�[���������u�Ԃ��H
	*	@param	nKey �L�[�ԍ�
	*	@return	bool �������u�Ԃ��ǂ���
	*/
	bool IsKeyTrigger(KEY key);

	/**
	*	�L�[�𗣂����u�Ԃ��H
	*	@param	nKey �L�[�ԍ�
	*	@return	bool �������u�Ԃ��ǂ���
	*/
	bool IsKeyRelease(KEY key);

	/**
	*	�L�[�𗣂����u�Ԃ܂����������Ă邩�H
	*	@param	nKey �L�[�ԍ�
	*	@return	bool �������u�Ԃ܂����������Ă邩�ǂ���
	*/
	bool IsKeyRepeat(KEY key);

private:
	/**
	*	�W���C�p�b�h�̗�
	*	@param	lpddi �f�o�C�X�̃C���X�^���X 
	*	@return	pvRef �����n�������|�C���^�[
	*/
	static BOOL CALLBACK EnumJoyCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef);

	/**
	*	�W���C�p�b�h�̎��ݒ�
	*	@param	lpddi �f�o�C�X�I�u�W�F�N�g�̃C���X�^���X 
	*	@return	pvRef �����n�������|�C���^�[
	*/
	static BOOL CALLBACK EnumAxesCallback(const LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);

	/**
	*	���͏��̐ݒ�
	*	@param	void
	*	@return	void
	*/
	void SetKeyState(void);

	/**
	*	�L�[���͔z�񏉊���
	*	@param	void
	*	@return	void
	*/
	void ClearState(void);

	DIJOYSTATE2		_joypadState;					// �W���C�p�b�h��Ԃ��󂯎�郏�[�N
	bool			_aKeyState			[KEY_MAX];	// �v���X���[�N
	bool			_aKeyStateTrigger	[KEY_MAX];	// �g���K�[���[�N
	bool			_aKeyStateRelease	[KEY_MAX];	// �����[�X���[�N
	bool			_aKeyStateRepeat	[KEY_MAX];	// ���s�[�g���[�N
	int				_aKeyStateRepeatCnt	[KEY_MAX];	// ���s�[�g�J�E���^
};
#endif
//End of File _INPUTJOYPAD_H_