//==============================================================================
// File		Input.h
// Comment	入力抽象クラス
// Author	TOMOHIRO KOUNO
// Create	2014年6月27日
//==============================================================================

//------------------------------------------------------------------------------
//	インクルードガード
//------------------------------------------------------------------------------
#ifndef _INPUT_H_
#define _INPUT_H_

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------
#define DIRECTINPUT_VERSION (0x0800)	// 警告対策

//------------------------------------------------------------------------------
//	インクルード
//------------------------------------------------------------------------------
#include "dinput.h"
#include "Common/Common.h"
#include "Common/System.h"

/**
* @brief 入力抽象クラス
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
	*	@param	hInst ハンドルインスタンス
	*	@param	hWnd  ハンドルウィンドウ
	*	@return	初期化に成功したか?
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