//==============================================================================
// File		InputJoypad.cpp
// Comment	ジョイパッド入力クラス
// Author	TOMOHIRO KOUNO
// Create	2014年6月27日
//==============================================================================

//------------------------------------------------------------------------------
//	インクルード
//------------------------------------------------------------------------------
#include "InputJoypad.h"

/**
* @brief Constructor
* @param	void
* @return	void
*/
CInputJoypad::CInputJoypad()
{
	ClearState();
}

/**
* @brief Destructor
*/
CInputJoypad::~CInputJoypad()
{
}

/**
*	Init JoyPad Device
*	@param	hInst ハンドルインスタンス
*	@param	hWnd  ハンドルウィンドウ
*	@return	初期化に成功したか?
*/
HRESULT CInputJoypad::Initialize(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	// 入力処理の初期化
	CInput::Initialize(hInst, hWnd);

	hr = _pDInput->EnumDevices(DI8DEVCLASS_GAMECTRL, CInputJoypad::EnumJoyCallback, this, DIEDFL_ATTACHEDONLY);
	if(FAILED(hr) || _pDIDevice == nullptr)
	{
//		MessageBox(hWnd, "ジョイパッドがありません！", "警告！", MB_ICONWARNING);
		return hr;
	}

	// データフォーマットを設定
	hr = _pDIDevice->SetDataFormat(&c_dfDIJoystick2);
	if(FAILED(hr))
	{
		MessageBox(hWnd, L"ジョイパッドのデータフォーマットを設定できませんでした。", L"警告！", MB_ICONWARNING);
		return hr;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hr = _pDIDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(hr))
	{
		MessageBox(hWnd, L"ジョイパッドの協調モードを設定できませんでした。", L"警告！", MB_ICONWARNING);
		return hr;
	}

	hr = _pDIDevice->EnumObjects(CInputJoypad::EnumAxesCallback, this, DIDFT_AXIS);
	if(FAILED(hr))
	{
		MessageBox(hWnd, L"ジョイパッドの・・・", L"警告！", MB_ICONWARNING);
		return hr;
	}

	// デバイスの設定
#if 0
	{
		DIPROPRANGE diprg;

		ZeroMemory(&diprg, sizeof(diprg));
		diprg.diph.dwSize = sizeof(diprg);
		diprg.diph.dwHeaderSize = sizeof(diprg.diph);

		diprg.diph.dwObj = DIJOFS_X;
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin       = JOY_MIN_X;
		diprg.lMax       = JOY_MAX_X;
		_pDIDevice->SetProperty(DIPROP_RANGE, &diprg.diph);	// Ｘ方向の範囲を指定

		diprg.diph.dwObj = DIJOFS_Y;
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin       = JOY_MIN_Y;
		diprg.lMax       = JOY_MAX_Y;
		_pDIDevice->SetProperty(DIPROP_RANGE, &diprg.diph);	// Ｙ方向の範囲を指定

		diprg.diph.dwObj = DIJOFS_RY;
		diprg.diph.dwHow = DIPH_BYOFFSET;
		diprg.lMin       = JOY_MIN_Y;
		diprg.lMax       = JOY_MAX_Y;
		_pDIDevice->SetProperty(DIPROP_RANGE, &diprg.diph);	// Ｙ方向の範囲を指定
	}
#endif

	// キーボードへのアクセス権を獲得(入力制御開始)
	_pDIDevice->Acquire();

	return hr;
}

/**
*	ジョイパッドの列挙
*	@param	lpddi デバイスのインスタンス 
*	@return	pvRef 引き渡したいポインター
*/
BOOL CALLBACK CInputJoypad::EnumJoyCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef)
{
	DIDEVCAPS	diDevCaps;			// デバイス情報
	HRESULT		hRes;
	CInputJoypad *pThis = reinterpret_cast<CInputJoypad*>(pvRef);

	// ジョイスティック用デバイスオブジェクトを作成
	hRes = pThis->_pDInput->CreateDevice(lpddi->guidInstance, &pThis->_pDIDevice,nullptr);
	if(FAILED(hRes))
	{
		return DIENUM_CONTINUE;		// 列挙を続ける
	}

	// ジョイスティックの能力を調べる
	diDevCaps.dwSize = sizeof(DIDEVCAPS);
	hRes = pThis->_pDIDevice->GetCapabilities(&diDevCaps);
	if(FAILED(hRes))
	{
		pThis->_pDIDevice->Release();
		pThis->_pDIDevice = nullptr;

		return DIENUM_CONTINUE;		// 列挙を続ける
	}

	return DIENUM_STOP;		// このデバイスを使うので列挙を終了する
}

/**
*	ジョイパッドの軸設定
*	@param	lpddi デバイスオブジェクトのインスタンス 
*	@return	pvRef 引き渡したいポインター
*/
BOOL CALLBACK CInputJoypad::EnumAxesCallback(const LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef)
{
	HRESULT hr;
	CInputJoypad *pThis = reinterpret_cast<CInputJoypad*>(pvRef);

	// 軸の値の範囲を設定（-1000〜1000）
	DIPROPRANGE diprg;
	ZeroMemory(&diprg, sizeof(diprg));
	diprg.diph.dwSize	= sizeof(diprg); 
	diprg.diph.dwHeaderSize	= sizeof(diprg.diph); 
	diprg.diph.dwObj	= lpddoi->dwType;
	diprg.diph.dwHow	= DIPH_BYID;
	diprg.lMin	= -1000;
	diprg.lMax	= +1000;
	hr = pThis->_pDIDevice->SetProperty(DIPROP_RANGE, &diprg.diph);
	if (FAILED(hr))
	{
		return DIENUM_STOP;
	}

	return DIENUM_CONTINUE;
}

/**
*	Uninitilaize JoyPad Device
*	@param	void
*	@return	void
*/
void CInputJoypad::Uninitialize(void)
{
	// 入力処理の開放
	CInput::Uninitialize();
}

/**
*	Update JoyPad Device Pure Fucntion
*	@param	void
*	@return	HRESULT 更新に成功したか
*/
void CInputJoypad::Update(void)
{
	HRESULT hr;
	bool aKeyStateOld[KEY_MAX];

	if(!_pDIDevice)
	{
		return;
	}

	// 前回のデータを保存
	for(int nCntKey = 0; nCntKey < KEY_MAX; nCntKey++)
	{
		aKeyStateOld[nCntKey] = _aKeyState[nCntKey];
	}

	// デバイスからデータを取得
	hr = _pDIDevice->GetDeviceState(sizeof(_joypadState), &_joypadState);
	if(SUCCEEDED(hr))
	{
		// キー情報設定
		SetKeyState();

		for(int nCntKey = 0; nCntKey < KEY_MAX; nCntKey++)
		{
			_aKeyStateTrigger[nCntKey] = (aKeyStateOld[nCntKey] ^ _aKeyState[nCntKey]) & _aKeyState[nCntKey];
			_aKeyStateRelease[nCntKey] = (aKeyStateOld[nCntKey] ^ _aKeyState[nCntKey]) & !_aKeyState[nCntKey];
			_aKeyStateRepeat[nCntKey] = _aKeyStateTrigger[nCntKey];

			if(_aKeyState[nCntKey])
			{
				_aKeyStateRepeatCnt[nCntKey]++;
				if(_aKeyStateRepeatCnt[nCntKey] >= 20)
				{
					_aKeyStateRepeat[nCntKey] = _aKeyState[nCntKey];
				}
			}
			else
			{
				_aKeyStateRepeatCnt[nCntKey] = 0;
				_aKeyStateRepeat[nCntKey] = 0;
			}
		}
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
*	入力情報の設定
*	@param	void
*	@return	void
*/
void CInputJoypad::SetKeyState(void)
{
	if(_joypadState.lX <= -8)
	{
		_aKeyState[KEY_LEFT] = true;
	}
	else
	{
		_aKeyState[KEY_LEFT] = false;
	}

	if(_joypadState.lX >= 8)
	{
		_aKeyState[KEY_RIGHT] = true;
	}
	else
	{
		_aKeyState[KEY_RIGHT] = false;
	}

	if(_joypadState.lY <= -8)
	{
		_aKeyState[KEY_UP] = true;
	}
	else
	{
		_aKeyState[KEY_UP] = false;
	}

	if(_joypadState.lY >= 8)
	{
		_aKeyState[KEY_DOWN] = true;
	}
	else
	{
		_aKeyState[KEY_DOWN] = false;
	}

	if(_joypadState.rgbButtons[0])
	{
		_aKeyState[KEY_JUMP] = true;
	}
	else
	{
		_aKeyState[KEY_JUMP] = false;
	}

	if(_joypadState.rgbButtons[1])
	{
		_aKeyState[KEY_SHOT] = true;
	}
	else
	{
		_aKeyState[KEY_SHOT] = false;
	}

	if(_joypadState.rgbButtons[6])
	{
		_aKeyState[KEY_TURN_LEFT] = true;
	}
	else
	{
		_aKeyState[KEY_TURN_LEFT] = false;
	}

	if(_joypadState.rgbButtons[8])
	{
		_aKeyState[KEY_TURN_RIGHT] = true;
	}
	else
	{
		_aKeyState[KEY_TURN_RIGHT] = false;
	}

	if(_joypadState.rgbButtons[7])
	{
		_aKeyState[KEY_TURN_UP] = true;
	}
	else
	{
		_aKeyState[KEY_TURN_UP] = false;
	}

	if(_joypadState.rgbButtons[9])
	{
		_aKeyState[KEY_TURN_DOWN] = true;
	}
	else
	{
		_aKeyState[KEY_TURN_DOWN] = false;
	}

	if(_joypadState.rgbButtons[11])
	{
		_aKeyState[KEY_START] = true;
	}
	else
	{
		_aKeyState[KEY_START] = false;
	}

	if(_joypadState.rgbButtons[10])
	{
		_aKeyState[KEY_SELECT] = true;
	}
	else
	{
		_aKeyState[KEY_SELECT] = false;
	}
}

/**
*	キーを押し続けてるか？
*	@param	nKey キー番号
*	@return	bool 押されてるかどうか
*/
bool CInputJoypad::IsKeyPress(KEY key)
{
	return _aKeyState[key];
}

/**
*	キーを押した瞬間か？
*	@param	nKey キー番号
*	@return	bool 押した瞬間かどうか
*/
bool CInputJoypad::IsKeyTrigger(KEY key)
{
	return _aKeyStateTrigger[key];
}

/**
*	キーを離した瞬間か？
*	@param	nKey キー番号
*	@return	bool 離した瞬間かどうか
*/
bool CInputJoypad::IsKeyRelease(KEY key)
{
	return _aKeyStateRelease[key];
}

/**
*	キーを離した瞬間また押し続けてるか？
*	@param	nKey キー番号
*	@return	bool 離した瞬間また押し続けてるかどうか
*/
bool CInputJoypad::IsKeyRepeat(KEY key)
{
	return _aKeyStateRepeat[key];
}

/**
*	キー入力配列初期化
*	@param	void
*	@return	void
*/
void CInputJoypad::ClearState(void)
{
	ZeroMemory(_aKeyState			,sizeof _aKeyState);
	ZeroMemory(_aKeyStateTrigger	,sizeof _aKeyStateTrigger);
	ZeroMemory(_aKeyStateRelease	,sizeof _aKeyStateRelease);
	ZeroMemory(_aKeyStateRepeat		,sizeof _aKeyStateRepeat);
	ZeroMemory(_aKeyStateRepeatCnt	,sizeof _aKeyStateRepeatCnt);
}