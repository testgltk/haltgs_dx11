//==============================================================================
// File		InputXInput.h
// Comment	XInputクラス
// Author	TOMOHIRO KOUNO
// Create	2014年12月20日
//==============================================================================

//------------------------------------------------------------------------------
//	インクルードガード
//------------------------------------------------------------------------------
#ifndef _INPUTXINPUT_H_
#define _INPUTXINPUT_H_

//------------------------------------------------------------------------------
//	インクルード
//------------------------------------------------------------------------------
#include "Common/Common.h"

/**
* @brief IInput入力クラス
*/
class CInputXInput
{
public:

	// 仮想キーボード配列
	typedef enum
	{
		VT_INPUT_LEFT = 0,
		VT_INPUT_RIGHT,
		VT_INPUT_UP,
		VT_INPUT_DOWN,
		VT_INPUT_R_LEFT,
		VT_INPUT_R_RIGHT,
		VT_INPUT_R_UP,
		VT_INPUT_R_DOWN,

		VT_INPUT_Y_OR_DELTA,	///> Y △
		VT_INPUT_B_OR_CIRCLE,	///> B ○
		VT_INPUT_A_OR_X,		///> A ×
		VT_INPUT_X_OR_RECT,		///> X □
		VT_INPUT_5,
		VT_INPUT_6,
		VT_INPUT_7,
		VT_INPUT_8,
		VT_INPUT_9,
		VT_INPUT_10,	// 適当に10個とっておく
		VT_INPUT_MAX,	// キーではない
	}VT_INPUT;

	typedef enum RSTICK_BUTTON_
	{
		RSTICK_BUTTON_UP,
		RSTICK_BUTTON_DONW,
		RSTICK_BUTTON_RIGHT,
		RSTICK_BUTTON_LEFT,
		RSTICK_BUTTON_MAX,
	}RSTICK_BUTTON;

	// キー情報のセーブ・ロード状態
	typedef enum
	{
		KEYSTATE_MODE_NONE = 0,	// 何もしていない
		KEYSTATE_MODE_SAVE,		// キー情報セーブ中
		KEYSTATE_MODE_LOAD,		// キー情報ロード中
	} KEYSTATE_MODE;
	/**
	* @brief Constructor
	* @param	void
	* @return	void
	*/
	CInputXInput(void);

	/**
	* @brief Destructor
	*/
	virtual ~CInputXInput(void);

	/**
	*	解放
	*	@param	void
	*	@return	void
	*/
	void Release(void);

	/**
	*	更新
	*	@param	void
	*	@return	void
	*/
	void Update(void);

	/**
	*	Xinput対応コントローラがあるか調べる
	*	@param	void
	*	@return	void
	*/
	bool GetEnableDevise(void);

	/**
	*	キーを押したか
	*	@param	とのキーか
	*	@param	とのパッドか
	*	@return	TRUE:	キーを押した
	*	@return	FALSE:	キーを押してない
	*/
	bool IsPress(VT_INPUT vk, int nPadID);

	/**
	*	キーを押した瞬間か
	*	@param	とのキーか
	*	@param	とのパッドか
	*	@return	TRUE:	キーを押した瞬間
	*	@return	FALSE:	キーを押した瞬間でない
	*/
	bool IsTrigger(VT_INPUT vk, int nPadID);

	/**
	*	キーを離した瞬間か
	*	@param	とのキーか
	*	@param	とのパッドか
	*	@return	TRUE:	キーを離した瞬間
	*	@return	FALSE:	キーを離した瞬間でない
	*/
	bool IsRelease(VT_INPUT vk, int nPadID);

	/**
	*	キーがリピートされたか
	*	@param	とのキーか
	*	@param	とのパッドか
	*	@return	TRUE:	キーがリピートされた
	*	@return	FALSE:	キーがリピートされてない
	*/
	bool IsRepeat(VT_INPUT vk, int nPadID);

	/**
	*	キーを押した瞬間か（デモ中でも入力受け取る）
	*	@param	とのキーか
	*	@param	とのパッドか
	*	@return	TRUE:	キーを押した瞬間
	*	@return	FALSE:	キーを押した瞬間でない
	*/
	bool IsTriggerDemo(VT_INPUT vk, int nPadID);

	/**
	*	コントローラの振動
	*	@param	左振動量(0～1.0f)
	*	@param	右振動量(0～1.0f)
	*	@param	とのパッドか
	*	@return	void
	*/
	void Shake(float left, float right,int nPadID);

	/**
	*	上下に該当するキーが押された
	*	@param	void
	*	@return	上キー : 1 下キー -1 無入力0
	*/
	float GetAxisVertical(void);

	/**
	*	左右に該当するキーが押された
	*	@param	void
	*	@return	右キー : 1 左キー -1 無入力0
	*/
	float GetAxisHorizontal(void);

	/**
	*	右スティックの判定関数
	*	@param	どのボタンか(右スティックの上下左右を指定)
	*	@param	どのパッドか
	*	@return	TRUE :押されている
	*	@return	FALSE:押されてない
	*/
	bool IsRStickPress(RSTICK_BUTTON Button, int nPadID);

	/**
	*	キー入力モードを設定
	*	@param	入力モードを指定
	*	@void
	*/
	void SetKeyStateMode(KEYSTATE_MODE KeyStateMode);

private:

	// パッド情報構造体
	typedef struct XINPUT_PAD_STATE_
	{
		XINPUT_STATE	xPadState;					///> パッドの現在情報を保持
		bool			isConnect;					///> 接続されているかどうか
	}XINPUT_PAD_STATE;

	static const int PAD_NUM = 2;					///> パッド個数
	XINPUT_PAD_STATE m_sPadState[PAD_NUM];			///> 現在のパッド状態
	XINPUT_PAD_STATE m_sPadStateOld[PAD_NUM];		///> 1F前のパッド状態
	DWORD m_InputVTKey[VT_INPUT_MAX];				///> 入力したか
	BYTE m_InputRepeatBuff[VT_INPUT_MAX][PAD_NUM];	///> リピート状態 
	int m_nRepeatStartTime[PAD_NUM];				///> リピート入力が始まるまでの時間(フレーム数)
	int m_nRepeatSleepTime[PAD_NUM];				///> リピート入力が繰り返すまでの時間(フレーム数)

	KEYSTATE_MODE m_KeyStateMode;					///> キー状態
	bool m_bRStickIsPress[RSTICK_BUTTON_MAX][PAD_NUM]; //右スティック上下左右
};
#endif
//End of File _INPUTXINPUT_H_