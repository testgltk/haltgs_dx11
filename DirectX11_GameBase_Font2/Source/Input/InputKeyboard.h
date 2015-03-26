//==============================================================================
// File		InputKeyboard.h
// Comment	キーボード入力クラス
// Author	TOMOHIRO KOUNO
// Create	2014年6月27日
//==============================================================================

//------------------------------------------------------------------------------
//	インクルードガード
//------------------------------------------------------------------------------
#ifndef _INPUTKEYBOARD_H_
#define _INPUTKEYBOARD_H_

//------------------------------------------------------------------------------
//	インクルード
//------------------------------------------------------------------------------
#include "Input/Input.h"
#include "Common/Common.h"
/**
* @brief キーボード入力クラス
*/
class CInputKeyboard : public CInput
{
public:

	enum {KEY_ARRAY_MAX = 256};	///> キー配列の最大数
	enum {REPEAT_TIME = 20};	///> キーリピートとみなす時間
	/**
	* @brief Constructor
	* @param	void
	* @return	void
	*/
	CInputKeyboard(void);

	/**
	* @brief Destructor
	*/
	~CInputKeyboard(void);

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

	/**
	*	Update Input Device Pure Fucntion
	*	@param	void
	*	@return	void
	*/
	void Update(void);

	/**
	*	キーを押し続けてるか？
	*	@param	nKey キー番号
	*	@return	BOOL 押されてるかどうか
	*/
	BOOL IsKeyPress		(int nKey);

	/**
	*	キーを押した瞬間か？
	*	@param	nKey	キー番号
	*	@param	bIgnore	デモ中にトリガー情報を
	*			ロードデータにしているのを一時的に無視する
	*			(デモ中にスキップを行う際には必要)
	*	@return	BOOL 押した瞬間かどうか
	*/
	BOOL IsKeyTrigger	(int nKey,bool bIgnore = false);

	/**
	*	キーを離した瞬間か？
	*	@param	nKey キー番号
	*	@return	BOOL 離した瞬間かどうか
	*/
	BOOL IsKeyRelease	(int nKey);

	/**
	*	キーを離した瞬間また押し続けてるか？
	*	@param	nKey キー番号
	*	@return	BOOL 離した瞬間また押し続けてるかどうか
	*/
	BOOL IsKeyRepeat	(int nKey);

	/**
	*	キー入力の消去
	*	@param	nKey キー番号
	*	@return	void
	*/
	void FlushKeyTrigger(int nKey);

	/**
	*	キー入力配列初期化
	*	@param	void
	*	@return	void
	*/
	void ClearState(void);

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
	*	キーデータ保存開始
	*	@param	void
	*	@return	TRUE : 保存開始成功
	*	@return	FALSE: 保存開始失敗
	*/
	bool StartSaveKeyState(void);

	/**
	*	キーデータ保存終了
	*	@param	void
	*	@return	TRUE : 保存終了成功
	*	@return	FALSE: 保存終了失敗
	*/
	bool EndSaveKeyState(void);

	/**
	*	キーデータ読み込み開始
	*	@param	void
	*	@return	TRUE : 読み込み開始成功
	*	@return	FALSE: 読み込み開始失敗
	*/
	bool StartLoadKeyState(void);

	/**
	*	キーデータ読み込み終了
	*	@param	void
	*	@return	TRUE : 読み込み終了成功
	*	@return	FALSE: 読み込み終了失敗
	*/
	bool EndLoadKeyState(void);

private:
	BYTE m_aKeyState			[KEY_ARRAY_MAX];	///> キーボードの状態を受け取るワーク
	BYTE m_aKeyStateTrigger		[KEY_ARRAY_MAX];	///> トリガーワーク
	BYTE m_aKeyStateRelease		[KEY_ARRAY_MAX];	///> リリースワーク
	BYTE m_aKeyStateRepeat		[KEY_ARRAY_MAX];	///> リピートワーク
	int	 m_aKeyStateRepeatCnt	[KEY_ARRAY_MAX];	///> リピートカウンタ

	// キー情報のセーブ・ロード状態
	typedef enum
	{
		KEYSTATE_MODE_NONE = 0,						///> 何もしていない
		KEYSTATE_MODE_SAVE,							///> キー情報セーブ中
		KEYSTATE_MODE_LOAD,							///> キー情報ロード中
	} KEYSTATE_MODE;


	//TO DEMO STATE
	static const int SAVE_FRAME = 3600;			///> キーステートを保存するフレーム数
	BYTE*			m_pFileKeyState;			///> セーブ・ロード用キー情報ワーク
	BYTE*			m_pFileKeyStateTrigger;		///> セーブ・ロード用キートリガーワーク
	BYTE*			m_pFileKeyStateRelease;		///> セーブ・ロード用キーリリースワーク
	BYTE*			m_pFileKeyStateRepeat;		///> セーブ・ロード用キーリピートワーク
	int				m_cntFrame;					///> ファイルセーブ・ロード中のフレームカウンタ
	KEYSTATE_MODE	m_keyStateMode;				///> キー情報のセーブ・ロード状態

	/**
	*	キーデータ保存処理
	*	@param	void
	*	@return	void
	*/
	void SaveKeyState(void);

	/**
	*	キーデータ読み込み処理
	*	@param	void
	*	@return	void
	*/
	void LoadKeyState(void);
};
#endif
//End of File _INPUTKEYBOARD_H_