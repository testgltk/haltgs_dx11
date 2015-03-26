//==============================================================================
// File		InputMouse.cpp
// Comment	�}�E�X���̓N���X
// Author	TOMOHIRO KOUNO
// Create	2014�N6��27��
//==============================================================================

//------------------------------------------------------------------------------
//	�C���N���[�h
//------------------------------------------------------------------------------
#include "InputMouse.h"


/**
* @brief Constructor
* @param	void
* @return	void
*/
CInputMouse::CInputMouse()
{
	ClearState();
}

/**
* @brief Destructor
*/
CInputMouse::~CInputMouse()
{
	ClearState();
}

/**
*	Init Mouse Device
*	@param	hInst �n���h���C���X�^���X
*	@param	hWnd  �n���h���E�B���h�E
*	@return	�������ɐ���������?
*/
HRESULT CInputMouse::Initialize(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	// ���͏����̏�����
	CInput::Initialize(hInst, hWnd);

	// �f�o�C�X�I�u�W�F�N�g���쐬
	hr = _pDInput->CreateDevice(GUID_SysMouse, &_pDIDevice, nullptr);
	if(FAILED(hr) || _pDIDevice == NULL)
	{
		MessageBox(hWnd, L"�}�E�X������܂���I", L"�x���I", MB_ICONWARNING);
		return hr;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	hr = _pDIDevice->SetDataFormat(&c_dfDIMouse2);
	if(FAILED(hr))
	{
		MessageBox(hWnd, L"�}�E�X�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", L"�x���I", MB_ICONWARNING);
		return hr;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = _pDIDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(hr))
	{
		MessageBox(hWnd, L"�}�E�X�̋������[�h��ݒ�ł��܂���ł����B", L"�x���I", MB_ICONWARNING);
		return hr;
	}

	// �f�o�C�X�̐ݒ�
	{
		DIPROPDWORD dipdw;

		dipdw.diph.dwSize = sizeof(dipdw);
		dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
		dipdw.diph.dwObj = 0;
		dipdw.diph.dwHow = DIPH_DEVICE;
		dipdw.dwData = DIPROPAXISMODE_REL;

		hr = _pDIDevice->SetProperty(DIPROP_AXISMODE, &dipdw.diph);
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	_pDIDevice->Acquire();

	return hr;
}

/**
*	Uninitilaize Mouse Device
*	@param	void
*	@return	void
*/
void CInputMouse::Uninitialize(void)
{
	// ���͏����̊J��
	ClearState();
	CInput::Uninitialize();
}

/**
*	Update Mouse Device Override
*	@param	void
*	@return	HRESULT �������擾�ł�����
*/
void CInputMouse::Update(void)
{
	HRESULT hr;
	DIMOUSESTATE2 mouseState;

	if(!_pDIDevice)
	{
		return;
	}

	// �f�o�C�X����f�[�^���擾
	hr = _pDIDevice->GetDeviceState(sizeof(mouseState), &mouseState);
	if(SUCCEEDED(hr))
	{
		_mouseStateTrigger.lX = ((_mouseState.lX ^ mouseState.lX) & mouseState.lX);
		_mouseStateTrigger.lY = ((_mouseState.lY ^ mouseState.lY) & mouseState.lY);
		_mouseStateTrigger.lZ = ((_mouseState.lZ ^ mouseState.lZ) & mouseState.lZ);
		for(int nCntKey = 0; nCntKey < MOUSEBUTTON_MAX; nCntKey++)
		{
			_mouseStateTrigger.rgbButtons[nCntKey]
				= ((_mouseState.rgbButtons[nCntKey] ^ mouseState.rgbButtons[nCntKey]) & mouseState.rgbButtons[nCntKey]);
		}

		_mouseState = mouseState;

		// �X�N���[�����W���擾
		GetCursorPos(&_posMouseWorld);
	}
	else
	{
		//���X�g���̌���͂����
		ClearState();
		_pDIDevice->Acquire();
	}

	return;
}

/**
*	�}�E�X�̍��{�^�������������Ă邩�H
*	@param	void
*	@return	BOOL ������Ă邩�ǂ���
*/
BOOL CInputMouse::IsLeftPress(void)
{
	return (_mouseState.rgbButtons[0] & 0x80) ? TRUE: FALSE;
}

/**
*	�}�E�X�̍��{�^�����������u�Ԃ��H
*	@param	void
*	@return	BOOL �������u�Ԃ��ǂ���
*/
BOOL CInputMouse::IsLeftTrigger(void)
{
	return (_mouseStateTrigger.rgbButtons[0] & 0x80) ? TRUE: FALSE;
}

/**
*	�}�E�X�̉E�{�^�������������Ă邩�H
*	@param	void
*	@return	BOOL ������Ă邩�ǂ���
*/
BOOL CInputMouse::IsRightPress(void)
{
	return (_mouseState.rgbButtons[1] & 0x80) ? TRUE: FALSE;
}

/**
*	�}�E�X�̉E�{�^�����������u�Ԃ��H
*	@param	void
*	@return	BOOL �������u�Ԃ��ǂ���
*/
BOOL CInputMouse::IsRightTrigger(void)
{
	return (_mouseStateTrigger.rgbButtons[1] & 0x80) ? TRUE: FALSE;
}

/**
*	�}�E�X�̒��{�^�������������Ă邩�H
*	@param	void
*	@return	BOOL ������Ă邩�ǂ���
*/
BOOL CInputMouse::IsCenterPress(void)
{
	return (_mouseState.rgbButtons[2] & 0x80) ? TRUE: FALSE;
}

/**
*	�}�E�X�̒��{�^�����������u�Ԃ��H
*	@param	void
*	@return	BOOL �������u�Ԃ��ǂ���
*/
BOOL CInputMouse::IsCenterTrigger(void)
{
	return (_mouseStateTrigger.rgbButtons[2] & 0x80) ? TRUE: FALSE;
}

/**
*	�}�E�XX���W�̎擾
*	@param	void
*	@return	LONG X���W
*/
LONG CInputMouse::GetAxisX(void)
{
	return _mouseState.lX;
}

/**
*	�}�E�XY���W�̎擾
*	@param	void
*	@return	LONG Y���W
*/
LONG CInputMouse::GetAxisY(void)
{
	return _mouseState.lY;
}

/**
*	�}�E�XZ���W�̎擾
*	@param	void
*	@return	LONG Z���W
*/
LONG CInputMouse::GetAxisZ(void)
{
	return _mouseState.lZ;
}

/**
*	�L�[���͔z�񏉊���
*	@param	void
*	@return	void
*/
void CInputMouse::ClearState(void)
{
	ZeroMemory(&_mouseState,		sizeof(_mouseState));
	ZeroMemory(&_mouseStateTrigger,	sizeof(_mouseStateTrigger));
}