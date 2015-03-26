//==============================================================================
// File		InputMouse.h
// Comment	�}�E�X���̓N���X
// Author	TOMOHIRO KOUNO
// Create	2014�N6��27��
//==============================================================================

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//	�C���N���[�h�K�[�h
//------------------------------------------------------------------------------
#ifndef _INPUTMOUSE_H_
#define _INPUTMOUSE_H_

//------------------------------------------------------------------------------
//	�C���N���[�h
//------------------------------------------------------------------------------
#include "Input/Input.h"
#include "Common/Common.h"
/**
* @brief �}�E�X���̓N���X
*/
class CInputMouse : public CInput
{
public:

	enum{MOUSEBUTTON_MAX = 8}; ///> �}�E�X�{�^���̍ő吔

	/**
	* @brief Constructor
	* @param	void
	* @return	void
	*/
	CInputMouse(void);

	/**
	* @brief Destructor
	*/
	~CInputMouse(void);

	/**
	*	Init Mouse Device
	*	@param	hInst �n���h���C���X�^���X
	*	@param	hWnd  �n���h���E�B���h�E
	*	@return	�������ɐ���������?
	*/
	HRESULT Initialize(HINSTANCE hInst, HWND hWnd);

	/**
	*	Uninitilaize Mouse Device
	*	@param	void
	*	@return	void
	*/
	void Uninitialize(void);

	/**
	*	Update Mouse Device Override
	*	@param	void
	*	@return	void
	*/
	void Update(void);

	/**
	*	�}�E�X�̍��{�^�������������Ă邩�H
	*	@param	void
	*	@return	BOOL ������Ă邩�ǂ���
	*/
	BOOL IsLeftPress	(void);

	/**
	*	�}�E�X�̍��{�^�����������u�Ԃ��H
	*	@param	void
	*	@return	BOOL �������u�Ԃ��ǂ���
	*/
	BOOL IsLeftTrigger	(void);

	/**
	*	�}�E�X�̉E�{�^�������������Ă邩�H
	*	@param	void
	*	@return	BOOL ������Ă邩�ǂ���
	*/
	BOOL IsRightPress	(void);

	/**
	*	�}�E�X�̉E�{�^�����������u�Ԃ��H
	*	@param	void
	*	@return	BOOL �������u�Ԃ��ǂ���
	*/
	BOOL IsRightTrigger	(void);

	/**
	*	�}�E�X�̒��{�^�������������Ă邩�H
	*	@param	void
	*	@return	BOOL ������Ă邩�ǂ���
	*/
	BOOL IsCenterPress	(void);

	/**
	*	�}�E�X�̒��{�^�����������u�Ԃ��H
	*	@param	void
	*	@return	BOOL �������u�Ԃ��ǂ���
	*/
	BOOL IsCenterTrigger(void);

	/**
	*	�}�E�XX���W�̎擾
	*	@param	void
	*	@return	LONG X���W
	*/
	LONG GetAxisX(void);

	/**
	*	�}�E�XY���W�̎擾
	*	@param	void
	*	@return	LONG Y���W
	*/
	LONG GetAxisY(void);

	/**
	*	�}�E�XZ���W�̎擾
	*	@param	void
	*	@return	LONG Z���W
	*/
	LONG GetAxisZ(void);

	/**
	*	�L�[���͔z�񏉊���
	*	@param	void
	*	@return	void
	*/
	void ClearState(void);

	/**
	*	�N���b�N�ꏊ�̃��[���h���W�𓾂�
	*	@param	void
	*	@return	LONG XY���W
	*/
	POINT *GetPosWorld(void){ return &_posMouseWorld; }

private:
	DIMOUSESTATE2	_mouseState;		///> �}�E�X�̏�Ԃ��󂯎�郏�[�N
	DIMOUSESTATE2	_mouseStateTrigger;	///> �g���K�[���[�N
	POINT			_posMouseWorld;		///> �}�E�X�̃X�N���[�����W
};
#endif
//End of File _INPUTMOUSE_H_