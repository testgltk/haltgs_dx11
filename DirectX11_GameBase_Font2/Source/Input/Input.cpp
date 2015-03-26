//==============================================================================
// File		Input.cpp
// Comment	���͒��ۃN���X
// Author	TOMOHIRO KOUNO
// Create	2014�N6��27��
//==============================================================================

//------------------------------------------------------------------------------
//	�C���N���[�h
//------------------------------------------------------------------------------
#include "Input/Input.h"



//------------------------------------------------------------------------------
//	�ÓI�ϐ�������
//------------------------------------------------------------------------------
LPDIRECTINPUT8	CInput::_pDInput = nullptr;

/**
* @brief Constructor
* @param	void
* @return	void
*/
CInput::CInput()
{
	_pDIDevice = NULL;
}

/**
* @brief Destructor
*/
CInput::~CInput()
{
}

/**
*	Init Input Device
*	@param	hInst �n���h���C���X�^���X
*	@param	hWnd  �n���h���E�B���h�E
*	@return	�������ɐ���������?
*/
HRESULT CInput::Initialize(HINSTANCE hInst, HWND hWnd)
{
	(void*)hWnd;
	HRESULT hr = S_FALSE;

	// DirectInput�I�u�W�F�N�g�̍쐬
	if(!_pDInput)
	{
		hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
									IID_IDirectInput8, (void**)&_pDInput,nullptr);
	}

	return hr;
}

/**
*	Uninitilaize Input Device
*	@param	void
*	@return	void
*/
void CInput::Uninitialize(void)
{
	// �f�o�C�X�I�u�W�F�N�g�̊J��
	if(_pDIDevice)
	{
		_pDIDevice->Unacquire();
		_pDIDevice->Release();
		_pDIDevice = nullptr;
	}

	// DirectInput�I�u�W�F�N�g�̊J��
	if(_pDInput)
	{
		_pDInput->Release();
		_pDInput = nullptr;
	}
}