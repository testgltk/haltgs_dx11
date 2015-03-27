//==============================================================================
// File		InputMouse.cpp
// Comment	マウス入力クラス
// Author	TOMOHIRO KOUNO
// Create	2014年6月27日
//==============================================================================

//------------------------------------------------------------------------------
//	インクルード
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
*	@param	hInst ハンドルインスタンス
*	@param	hWnd  ハンドルウィンドウ
*	@return	初期化に成功したか?
*/
HRESULT CInputMouse::Initialize(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	// 入力処理の初期化
	CInput::Initialize(hInst, hWnd);

	// デバイスオブジェクトを作成
	hr = _pDInput->CreateDevice(GUID_SysMouse, &_pDIDevice, nullptr);
	if(FAILED(hr) || _pDIDevice == NULL)
	{
		MessageBox(hWnd, L"マウスがありません！", L"警告！", MB_ICONWARNING);
		return hr;
	}

	// データフォーマットを設定
	hr = _pDIDevice->SetDataFormat(&c_dfDIMouse2);
	if(FAILED(hr))
	{
		MessageBox(hWnd, L"マウスのデータフォーマットを設定できませんでした。", L"警告！", MB_ICONWARNING);
		return hr;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hr = _pDIDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(hr))
	{
		MessageBox(hWnd, L"マウスの協調モードを設定できませんでした。", L"警告！", MB_ICONWARNING);
		return hr;
	}

	// デバイスの設定
	{
		DIPROPDWORD dipdw;

		dipdw.diph.dwSize = sizeof(dipdw);
		dipdw.diph.dwHeaderSize = sizeof(dipdw.diph);
		dipdw.diph.dwObj = 0;
		dipdw.diph.dwHow = DIPH_DEVICE;
		dipdw.dwData = DIPROPAXISMODE_REL;

		hr = _pDIDevice->SetProperty(DIPROP_AXISMODE, &dipdw.diph);
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
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
	// 入力処理の開放
	ClearState();
	CInput::Uninitialize();
}

/**
*	Update Mouse Device Override
*	@param	void
*	@return	HRESULT 正しく取得できたか
*/
void CInputMouse::Update(void)
{
	HRESULT hr;
	DIMOUSESTATE2 mouseState;

	if(!_pDIDevice)
	{
		return;
	}

	// デバイスからデータを取得
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

			_mouseStateRelease.rgbButtons[nCntKey]
				= ((_mouseState.rgbButtons[nCntKey] ^ mouseState.rgbButtons[nCntKey]) & ~mouseState.rgbButtons[nCntKey]);
		}

		_mouseState = mouseState;

		// スクリーン座標を取得
		GetCursorPos(&_posMouseWorld);
	}
	else
	{
		//ロスト時の誤入力を回避
		ClearState();
		_pDIDevice->Acquire();
	}

	return;
}

/**
*	マウスの左ボタンを押し続けてるか？
*	@param	void
*	@return	BOOL 押されてるかどうか
*/
BOOL CInputMouse::IsLeftPress(void)
{
	return (_mouseState.rgbButtons[0] & 0x80) ? TRUE: FALSE;
}

/**
*	マウスの左ボタンを押した瞬間か？
*	@param	void
*	@return	BOOL 押した瞬間かどうか
*/
BOOL CInputMouse::IsLeftTrigger(void)
{
	return (_mouseStateTrigger.rgbButtons[0] & 0x80) ? TRUE: FALSE;
}

/**
*	マウスの左ボタンを離した瞬間か？
*	@param	void
*	@return	BOOL 離した瞬間かどうか
*/
BOOL CInputMouse::IsLeftRelease(void)
{
	return (_mouseStateRelease.rgbButtons[0] & 0x80) ? TRUE : FALSE;
}

/**
*	マウスの右ボタンを押し続けてるか？
*	@param	void
*	@return	BOOL 押されてるかどうか
*/
BOOL CInputMouse::IsRightPress(void)
{
	return (_mouseState.rgbButtons[1] & 0x80) ? TRUE: FALSE;
}

/**
*	マウスの右ボタンを押した瞬間か？
*	@param	void
*	@return	BOOL 押した瞬間かどうか
*/
BOOL CInputMouse::IsRightTrigger(void)
{
	return (_mouseStateTrigger.rgbButtons[1] & 0x80) ? TRUE: FALSE;
}

/**
*	マウスの中ボタンを押し続けてるか？
*	@param	void
*	@return	BOOL 押されてるかどうか
*/
BOOL CInputMouse::IsCenterPress(void)
{
	return (_mouseState.rgbButtons[2] & 0x80) ? TRUE: FALSE;
}

/**
*	マウスの中ボタンを押した瞬間か？
*	@param	void
*	@return	BOOL 押した瞬間かどうか
*/
BOOL CInputMouse::IsCenterTrigger(void)
{
	return (_mouseStateTrigger.rgbButtons[2] & 0x80) ? TRUE: FALSE;
}

/**
*	マウスX座標の取得
*	@param	void
*	@return	LONG X座標
*/
LONG CInputMouse::GetAxisX(void)
{
	return _mouseState.lX;
}

/**
*	マウスY座標の取得
*	@param	void
*	@return	LONG Y座標
*/
LONG CInputMouse::GetAxisY(void)
{
	return _mouseState.lY;
}

/**
*	マウスZ座標の取得
*	@param	void
*	@return	LONG Z座標
*/
LONG CInputMouse::GetAxisZ(void)
{
	return _mouseState.lZ;
}

/**
*	キー入力配列初期化
*	@param	void
*	@return	void
*/
void CInputMouse::ClearState(void)
{
	ZeroMemory(&_mouseState,		sizeof(_mouseState));
	ZeroMemory(&_mouseStateTrigger,	sizeof(_mouseStateTrigger));
}