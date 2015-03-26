//==============================================================================
// File		Input.cpp
// Comment	入力抽象クラス
// Author	TOMOHIRO KOUNO
// Create	2014年6月27日
//==============================================================================

//------------------------------------------------------------------------------
//	インクルード
//------------------------------------------------------------------------------
#include "Input/Input.h"



//------------------------------------------------------------------------------
//	静的変数初期化
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
*	@param	hInst ハンドルインスタンス
*	@param	hWnd  ハンドルウィンドウ
*	@return	初期化に成功したか?
*/
HRESULT CInput::Initialize(HINSTANCE hInst, HWND hWnd)
{
	(void*)hWnd;
	HRESULT hr = S_FALSE;

	// DirectInputオブジェクトの作成
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
	// デバイスオブジェクトの開放
	if(_pDIDevice)
	{
		_pDIDevice->Unacquire();
		_pDIDevice->Release();
		_pDIDevice = nullptr;
	}

	// DirectInputオブジェクトの開放
	if(_pDInput)
	{
		_pDInput->Release();
		_pDInput = nullptr;
	}
}