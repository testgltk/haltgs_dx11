//==============================================================================
// File		InputJoypad.h
// Comment	ジョイパッド入力クラス
// Author	TOMOHIRO KOUNO
// Create	2014年6月27日
//==============================================================================

//------------------------------------------------------------------------------
//	インクルードガード
//------------------------------------------------------------------------------
#ifndef _INPUTJOYPAD_H_
#define _INPUTJOYPAD_H_

//------------------------------------------------------------------------------
//	インクルード
//------------------------------------------------------------------------------
#include "Input/Input.h"
#include "Common/Common.h"
/**
* @brief ジョイパッド入力クラス
*/
class CInputJoypad : CInput
{
public:
	/**
	* @brief Constructor
	* @param	void
	* @return	void
	*/
	CInputJoypad(void);

	/**
	* @brief Destructor
	*/
	~CInputJoypad(void);

	/**
	*	Init JoyPad Device
	*	@param	hInst ハンドルインスタンス
	*	@param	hWnd  ハンドルウィンドウ
	*	@return	初期化に成功したか?
	*/
	HRESULT Initialize(HINSTANCE hInst, HWND hWnd);

	/**
	*	Uninitilaize JoyPad Device
	*	@param	void
	*	@return	void
	*/
	void Uninitialize(void);

	/**
	*	Update JoyPad Device Pure Fucntion
	*	@param	void
	*	@return	void
	*/
	void Update(void);

	// キーの種類
	typedef enum
	{
		KEY_LEFT = 0,
		KEY_RIGHT,
		KEY_UP,
		KEY_DOWN,
		KEY_JUMP,
		KEY_SHOT,
		KEY_TURN_LEFT,
		KEY_TURN_RIGHT,
		KEY_TURN_UP,
		KEY_TURN_DOWN,
		KEY_START,
		KEY_SELECT,
		KEY_MAX
	} KEY;

	/**
	*	キーを押し続けてるか？
	*	@param	nKey キー番号
	*	@return	bool 押されてるかどうか
	*/
	bool IsKeyPress(KEY key);

	/**
	*	キーを押した瞬間か？
	*	@param	nKey キー番号
	*	@return	bool 押した瞬間かどうか
	*/
	bool IsKeyTrigger(KEY key);

	/**
	*	キーを離した瞬間か？
	*	@param	nKey キー番号
	*	@return	bool 離した瞬間かどうか
	*/
	bool IsKeyRelease(KEY key);

	/**
	*	キーを離した瞬間また押し続けてるか？
	*	@param	nKey キー番号
	*	@return	bool 離した瞬間また押し続けてるかどうか
	*/
	bool IsKeyRepeat(KEY key);

private:
	/**
	*	ジョイパッドの列挙
	*	@param	lpddi デバイスのインスタンス 
	*	@return	pvRef 引き渡したいポインター
	*/
	static BOOL CALLBACK EnumJoyCallback(const DIDEVICEINSTANCE* lpddi, VOID* pvRef);

	/**
	*	ジョイパッドの軸設定
	*	@param	lpddi デバイスオブジェクトのインスタンス 
	*	@return	pvRef 引き渡したいポインター
	*/
	static BOOL CALLBACK EnumAxesCallback(const LPCDIDEVICEOBJECTINSTANCE lpddoi, LPVOID pvRef);

	/**
	*	入力情報の設定
	*	@param	void
	*	@return	void
	*/
	void SetKeyState(void);

	/**
	*	キー入力配列初期化
	*	@param	void
	*	@return	void
	*/
	void ClearState(void);

	DIJOYSTATE2		_joypadState;					// ジョイパッド状態を受け取るワーク
	bool			_aKeyState			[KEY_MAX];	// プレスワーク
	bool			_aKeyStateTrigger	[KEY_MAX];	// トリガーワーク
	bool			_aKeyStateRelease	[KEY_MAX];	// リリースワーク
	bool			_aKeyStateRepeat	[KEY_MAX];	// リピートワーク
	int				_aKeyStateRepeatCnt	[KEY_MAX];	// リピートカウンタ
};
#endif
//End of File _INPUTJOYPAD_H_