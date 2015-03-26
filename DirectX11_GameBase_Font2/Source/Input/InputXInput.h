//==============================================================================
// File		InputXInput.h
// Comment	XInput�N���X
// Author	TOMOHIRO KOUNO
// Create	2014�N12��20��
//==============================================================================

//------------------------------------------------------------------------------
//	�C���N���[�h�K�[�h
//------------------------------------------------------------------------------
#ifndef _INPUTXINPUT_H_
#define _INPUTXINPUT_H_

//------------------------------------------------------------------------------
//	�C���N���[�h
//------------------------------------------------------------------------------
#include "Common/Common.h"

/**
* @brief IInput���̓N���X
*/
class CInputXInput
{
public:

	// ���z�L�[�{�[�h�z��
	typedef enum
	{
		VT_INPUT_LEFT = 0,
		VT_INPUT_RIGHT,
		VT_INPUT_UP,
		VT_INPUT_DOWN,
		VT_INPUT_R_LEFT,
		VT_INPUT_R_RIGHT,
		VT_INPUT_R_UP,
		VT_INPUT_R_DOWN,

		VT_INPUT_Y_OR_DELTA,	///> Y ��
		VT_INPUT_B_OR_CIRCLE,	///> B ��
		VT_INPUT_A_OR_X,		///> A �~
		VT_INPUT_X_OR_RECT,		///> X ��
		VT_INPUT_5,
		VT_INPUT_6,
		VT_INPUT_7,
		VT_INPUT_8,
		VT_INPUT_9,
		VT_INPUT_10,	// �K����10�Ƃ��Ă���
		VT_INPUT_MAX,	// �L�[�ł͂Ȃ�
	}VT_INPUT;

	typedef enum RSTICK_BUTTON_
	{
		RSTICK_BUTTON_UP,
		RSTICK_BUTTON_DONW,
		RSTICK_BUTTON_RIGHT,
		RSTICK_BUTTON_LEFT,
		RSTICK_BUTTON_MAX,
	}RSTICK_BUTTON;

	// �L�[���̃Z�[�u�E���[�h���
	typedef enum
	{
		KEYSTATE_MODE_NONE = 0,	// �������Ă��Ȃ�
		KEYSTATE_MODE_SAVE,		// �L�[���Z�[�u��
		KEYSTATE_MODE_LOAD,		// �L�[��񃍁[�h��
	} KEYSTATE_MODE;
	/**
	* @brief Constructor
	* @param	void
	* @return	void
	*/
	CInputXInput(void);

	/**
	* @brief Destructor
	*/
	virtual ~CInputXInput(void);

	/**
	*	���
	*	@param	void
	*	@return	void
	*/
	void Release(void);

	/**
	*	�X�V
	*	@param	void
	*	@return	void
	*/
	void Update(void);

	/**
	*	Xinput�Ή��R���g���[�������邩���ׂ�
	*	@param	void
	*	@return	void
	*/
	bool GetEnableDevise(void);

	/**
	*	�L�[����������
	*	@param	�Ƃ̃L�[��
	*	@param	�Ƃ̃p�b�h��
	*	@return	TRUE:	�L�[��������
	*	@return	FALSE:	�L�[�������ĂȂ�
	*/
	bool IsPress(VT_INPUT vk, int nPadID);

	/**
	*	�L�[���������u�Ԃ�
	*	@param	�Ƃ̃L�[��
	*	@param	�Ƃ̃p�b�h��
	*	@return	TRUE:	�L�[���������u��
	*	@return	FALSE:	�L�[���������u�ԂłȂ�
	*/
	bool IsTrigger(VT_INPUT vk, int nPadID);

	/**
	*	�L�[�𗣂����u�Ԃ�
	*	@param	�Ƃ̃L�[��
	*	@param	�Ƃ̃p�b�h��
	*	@return	TRUE:	�L�[�𗣂����u��
	*	@return	FALSE:	�L�[�𗣂����u�ԂłȂ�
	*/
	bool IsRelease(VT_INPUT vk, int nPadID);

	/**
	*	�L�[�����s�[�g���ꂽ��
	*	@param	�Ƃ̃L�[��
	*	@param	�Ƃ̃p�b�h��
	*	@return	TRUE:	�L�[�����s�[�g���ꂽ
	*	@return	FALSE:	�L�[�����s�[�g����ĂȂ�
	*/
	bool IsRepeat(VT_INPUT vk, int nPadID);

	/**
	*	�L�[���������u�Ԃ��i�f�����ł����͎󂯎��j
	*	@param	�Ƃ̃L�[��
	*	@param	�Ƃ̃p�b�h��
	*	@return	TRUE:	�L�[���������u��
	*	@return	FALSE:	�L�[���������u�ԂłȂ�
	*/
	bool IsTriggerDemo(VT_INPUT vk, int nPadID);

	/**
	*	�R���g���[���̐U��
	*	@param	���U����(0�`1.0f)
	*	@param	�E�U����(0�`1.0f)
	*	@param	�Ƃ̃p�b�h��
	*	@return	void
	*/
	void Shake(float left, float right,int nPadID);

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
	*	�E�X�e�B�b�N�̔���֐�
	*	@param	�ǂ̃{�^����(�E�X�e�B�b�N�̏㉺���E���w��)
	*	@param	�ǂ̃p�b�h��
	*	@return	TRUE :������Ă���
	*	@return	FALSE:������ĂȂ�
	*/
	bool IsRStickPress(RSTICK_BUTTON Button, int nPadID);

	/**
	*	�L�[���̓��[�h��ݒ�
	*	@param	���̓��[�h���w��
	*	@void
	*/
	void SetKeyStateMode(KEYSTATE_MODE KeyStateMode);

private:

	// �p�b�h���\����
	typedef struct XINPUT_PAD_STATE_
	{
		XINPUT_STATE	xPadState;					///> �p�b�h�̌��ݏ���ێ�
		bool			isConnect;					///> �ڑ�����Ă��邩�ǂ���
	}XINPUT_PAD_STATE;

	static const int PAD_NUM = 2;					///> �p�b�h��
	XINPUT_PAD_STATE m_sPadState[PAD_NUM];			///> ���݂̃p�b�h���
	XINPUT_PAD_STATE m_sPadStateOld[PAD_NUM];		///> 1F�O�̃p�b�h���
	DWORD m_InputVTKey[VT_INPUT_MAX];				///> ���͂�����
	BYTE m_InputRepeatBuff[VT_INPUT_MAX][PAD_NUM];	///> ���s�[�g��� 
	int m_nRepeatStartTime[PAD_NUM];				///> ���s�[�g���͂��n�܂�܂ł̎���(�t���[����)
	int m_nRepeatSleepTime[PAD_NUM];				///> ���s�[�g���͂��J��Ԃ��܂ł̎���(�t���[����)

	KEYSTATE_MODE m_KeyStateMode;					///> �L�[���
	bool m_bRStickIsPress[RSTICK_BUTTON_MAX][PAD_NUM]; //�E�X�e�B�b�N�㉺���E
};
#endif
//End of File _INPUTXINPUT_H_