//==============================================================================
// File		InputMouse.h
// Comment	マウス入力クラス
// Author	TOMOHIRO KOUNO
// Create	2014年6月27日
//==============================================================================

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//	インクルードガード
//------------------------------------------------------------------------------
#ifndef _INPUTMOUSE_H_
#define _INPUTMOUSE_H_

//------------------------------------------------------------------------------
//	インクルード
//------------------------------------------------------------------------------
#include "Input/Input.h"
#include "Common/Common.h"
/**
* @brief マウス入力クラス
*/
class CInputMouse : public CInput
{
public:

	enum{MOUSEBUTTON_MAX = 8}; ///> マウスボタンの最大数

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
	*	@param	hInst ハンドルインスタンス
	*	@param	hWnd  ハンドルウィンドウ
	*	@return	初期化に成功したか?
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
	*	マウスの左ボタンを押し続けてるか？
	*	@param	void
	*	@return	BOOL 押されてるかどうか
	*/
	BOOL IsLeftPress	(void);

	/**
	*	マウスの左ボタンを押した瞬間か？
	*	@param	void
	*	@return	BOOL 押した瞬間かどうか
	*/
	BOOL IsLeftTrigger	(void);

	/**
	*	マウスの右ボタンを押し続けてるか？
	*	@param	void
	*	@return	BOOL 押されてるかどうか
	*/
	BOOL IsRightPress	(void);

	/**
	*	マウスの右ボタンを押した瞬間か？
	*	@param	void
	*	@return	BOOL 押した瞬間かどうか
	*/
	BOOL IsRightTrigger	(void);

	/**
	*	マウスの中ボタンを押し続けてるか？
	*	@param	void
	*	@return	BOOL 押されてるかどうか
	*/
	BOOL IsCenterPress	(void);

	/**
	*	マウスの中ボタンを押した瞬間か？
	*	@param	void
	*	@return	BOOL 押した瞬間かどうか
	*/
	BOOL IsCenterTrigger(void);

	/**
	*	マウスX座標の取得
	*	@param	void
	*	@return	LONG X座標
	*/
	LONG GetAxisX(void);

	/**
	*	マウスY座標の取得
	*	@param	void
	*	@return	LONG Y座標
	*/
	LONG GetAxisY(void);

	/**
	*	マウスZ座標の取得
	*	@param	void
	*	@return	LONG Z座標
	*/
	LONG GetAxisZ(void);

	/**
	*	キー入力配列初期化
	*	@param	void
	*	@return	void
	*/
	void ClearState(void);

	/**
	*	クリック場所のワールド座標を得る
	*	@param	void
	*	@return	LONG XY座標
	*/
	POINT *GetPosWorld(void){ return &_posMouseWorld; }

private:
	DIMOUSESTATE2	_mouseState;		///> マウスの状態を受け取るワーク
	DIMOUSESTATE2	_mouseStateTrigger;	///> トリガーワーク
	POINT			_posMouseWorld;		///> マウスのスクリーン座標
};
#endif
//End of File _INPUTMOUSE_H_