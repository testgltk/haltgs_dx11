//==============================================================================
// File		Input.h
// Comment	���͒��ۃN���X
// Author	TOMOHIRO KOUNO
// Create	2014�N6��27��
//==============================================================================

//------------------------------------------------------------------------------
//	�C���N���[�h�K�[�h
//------------------------------------------------------------------------------
#ifndef _INPUT_H_
#define _INPUT_H_

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------
#define DIRECTINPUT_VERSION (0x0800)	// �x���΍�

//------------------------------------------------------------------------------
//	�C���N���[�h
//------------------------------------------------------------------------------
#include "dinput.h"
#include "Common/Common.h"
#include "Common/System.h"

/**
* @brief ���͒��ۃN���X
*/
class CInput :public ISystem
{
public:
	/**
	* @brief Constructor
	* @param	void
	* @return	void
	*/
	CInput(void);

	/**
	* @brief Destructor
	*/
	virtual ~CInput(void);

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

	void Finalize(void){ Uninitialize(); }

	/**
	*	Update Input Device Pure Fucntion
	*	@param	void
	*	@return	void
	*/
	virtual void Update(void){}

protected:
	LPDIRECTINPUTDEVICE8		_pDIDevice;	///> IDirectInputDevice8InterfacePointer
	static LPDIRECTINPUT8		_pDInput;	///> IDirectInput8InterfacePointer
private:
};
#endif
//End of File _INPUT_H_