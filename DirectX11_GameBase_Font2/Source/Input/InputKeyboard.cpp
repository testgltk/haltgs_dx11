//==============================================================================
// File		InputKeyboard.cpp
// Comment	キーボード入力クラス
// Author	TOMOHIRO KOUNO
// Create	2014年6月27日
//==============================================================================

//------------------------------------------------------------------------------
//	インクルード
//------------------------------------------------------------------------------
#include "Input/InputKeyboard.h"
#include <stdio.h>

/**
* @brief Constructor
* @param	void
* @return	void
*/
CInputKeyboard::CInputKeyboard()
{
	// 各ワークのクリア
	ClearState();
}

/**
* @brief Destructor
*/
CInputKeyboard::~CInputKeyboard()
{
	// 各ワークのクリア
	ClearState();
}

/**
*	Init Input Device
*	@param	hInst ハンドルインスタンス
*	@param	hWnd  ハンドルウィンドウ
*	@return	初期化に成功したか?
*/
HRESULT CInputKeyboard::Initialize(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	// 入力処理の初期化
	CInput::Initialize(hInst, hWnd);

	

	// デバイスオブジェクトを作成
	hr = _pDInput->CreateDevice(GUID_SysKeyboard, &_pDIDevice, nullptr);
	if(FAILED(hr) || _pDIDevice == nullptr)
	{
		MessageBox(hWnd, L"キーボードがありません！", L"警告！", MB_ICONWARNING);
		return hr;
	}

	// データフォーマットを設定
	hr = _pDIDevice->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr))
	{
		MessageBox(hWnd, L"キーボードのデータフォーマットを設定できませんでした。", L"警告！", MB_ICONWARNING);
		return hr;
	}

	// 協調モード設定（フォアグラウンド＆非排他モード）
	hr = _pDIDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(hr))
	{
		MessageBox(hWnd, L"キーボードの協調モードを設定できませんでした。", L"警告！", MB_ICONWARNING);
		return hr;
	}

	//アクセス権を獲得(入力制御開始)
	_pDIDevice->Acquire();

	// キー情報セーブ・ロードに関する初期化
	m_cntFrame = 0;							// フレームカウンタ
	m_pFileKeyState = NULL;					// セーブ・ロード用キー情報ワーク
	m_pFileKeyStateTrigger = NULL;			// セーブ・ロード用キートリガー情報ワーク
	m_pFileKeyStateRelease = NULL;			// セーブ・ロード用キーリリース情報ワーク
	m_pFileKeyStateRepeat = NULL;			// セーブ・ロード用キーリピート情報ワーク
	m_keyStateMode = KEYSTATE_MODE_NONE;	// キー情報のセーブ・ロード状態
	//m_keyStateMode = KEYSTATE_MODE_SAVE;

	//StartSaveKeyState();
	//StartLoadKeyState();

	return hr;
}

/**
*	Uninitilaize Input Device
*	@param	void
*	@return	void
*/
void CInputKeyboard::Uninitialize(void)
{
	// 入力処理の開放
	CInput::Uninitialize();

	//EndSaveKeyState();
	//EndLoadKeyState();
}

/**
*	Update Input Device Pure Fucntion
*	@param	void
*	@return	void
*/
void CInputKeyboard::Update(void)
{
	HRESULT hr;
	BYTE aKeyState[KEY_ARRAY_MAX];

	if(!_pDIDevice)
	{
		return;
	}

	// キー情報をロード中だったら
	if (m_keyStateMode == KEYSTATE_MODE_LOAD)
	{
		// ロード中の処理を行う
		LoadKeyState();
	}

	hr = _pDIDevice->GetDeviceState(sizeof(aKeyState), aKeyState);

	///*// キー情報をロード中だったら
	//if(m_keyStateMode == KEYSTATE_MODE_LOAD)
	//{
	//// 外部ファイルからデータを取得
	//LoadKeyState();
	//hr = S_OK;
	//}
	//// キー情報をロード中じゃなかったら
	//else
	//{
	//// デバイスからデータを取得
	//hr = _pDIDevice->GetDeviceState(sizeof(m_aKeyState), m_aKeyState);
	//}
	//*/

	if(SUCCEEDED(hr))
	{
		for(int nCntKey = 0; nCntKey < KEY_ARRAY_MAX; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey]	= (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];
			m_aKeyStateRelease[nCntKey]	= (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & ~aKeyState[nCntKey];
			//m_aKeyStateRepeat[nCntKey]	= m_aKeyStateTrigger[nCntKey];

			if(aKeyState[nCntKey])
			{
				m_aKeyStateRepeatCnt[nCntKey]++;
				if (m_aKeyStateRepeatCnt[nCntKey] == 1 || m_aKeyStateRepeatCnt[nCntKey] >= REPEAT_TIME)
				{
					m_aKeyStateRepeat[nCntKey] = aKeyState[nCntKey];
				}
				else
				{
					m_aKeyStateRepeat[nCntKey] = 0;
				}
			}
			else
			{
				m_aKeyStateRepeatCnt[nCntKey] = 0;
				m_aKeyStateRepeat[nCntKey] = 0;
			}

			m_aKeyState[nCntKey] = aKeyState[nCntKey];
		}
	}
	else
	{
		//キークリア ロスト時の誤入力を回避
		ClearState();
		_pDIDevice->Acquire();
	}

	// キー情報セーブ中だったら
	if (m_keyStateMode == KEYSTATE_MODE_SAVE)
	{
		// キーステートデータの保存
		SaveKeyState();
	}

	return;
}

/**
*	キーを押し続けてるか？
*	@param	nKey キー番号
*	@return	BOOL 押されてるかどうか
*/
BOOL CInputKeyboard::IsKeyPress(int nKey)
{
	//return (m_aKeyState[nKey] & 0x80) ? TRUE: FALSE;
	if (m_keyStateMode == KEYSTATE_MODE_LOAD)
	{
		// ロードしたキー情報を取得
		return (*(m_pFileKeyState + (m_cntFrame * 256) + nKey) & 0x80) ? TRUE : FALSE;
	}
	// ロードしていない、またはロード無視する場合
	else
	{
		// 現在のキー情報を取得
		return (m_aKeyState[nKey] & 0x80) ? TRUE : FALSE;
	}
}

/**
*	キーを押した瞬間か？
*	@param	nKey キー番号
*	@return	BOOL 押した瞬間かどうか
*/
BOOL CInputKeyboard::IsKeyTrigger(int nKey,bool bIgnore)
{
	//return (m_aKeyStateTrigger[nKey] & 0x80) ? TRUE: FALSE;

	if (m_keyStateMode == KEYSTATE_MODE_LOAD && !bIgnore)
	{
		// ロードしたキー情報を取得
		return (*(m_pFileKeyStateTrigger + (m_cntFrame * 256) + nKey) & 0x80) ? TRUE : FALSE;
	}
	// ロードしていない、またはロード無視する場合
	else
	{
		// 現在のキー情報を取得
		return (m_aKeyStateTrigger[nKey] & 0x80) ? TRUE : FALSE;
	}
}

/**
*	キーを離した瞬間か？
*	@param	nKey キー番号
*	@return	BOOL 離した瞬間かどうか
*/
BOOL CInputKeyboard::IsKeyRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? TRUE: FALSE;
}

/**
*	キーを離した瞬間また押し続けてるか？
*	@param	nKey キー番号
*	@return	BOOL 離した瞬間また押し続けてるかどうか
*/
BOOL CInputKeyboard::IsKeyRepeat(int nKey)
{
	return (m_aKeyStateRepeat[nKey] & 0x80) ? TRUE: FALSE;
}

/**
*	キー入力の消去
*	@param	nKey キー番号
*	@return	void
*/
void CInputKeyboard::FlushKeyTrigger(int nKey)
{
	m_aKeyStateTrigger[nKey] = 0;
}

/**
*	キー入力配列初期化
*	@param	void
*	@return	void
*/
void CInputKeyboard::ClearState(void)
{
	ZeroMemory(m_aKeyState			,sizeof (m_aKeyState));
	ZeroMemory(m_aKeyStateTrigger	,sizeof (m_aKeyStateTrigger));
	ZeroMemory(m_aKeyStateRelease	,sizeof (m_aKeyStateRelease));
	ZeroMemory(m_aKeyStateRepeat		,sizeof (m_aKeyStateRepeat));
	ZeroMemory(m_aKeyStateRepeatCnt	,sizeof (m_aKeyStateRepeatCnt));
}

/**
*	上下に該当するキーが押された
*	@param	void
*	@return	上キー : 1 下キー -1 無入力0
*/
float CInputKeyboard::GetAxisVertical(void)
{
	return IsKeyPress(DIK_W) ? 1.0f : IsKeyPress(DIK_S) ? -1.0f : 0.0f;
}

/**
*	左右に該当するキーが押された
*	@param	void
*	@return	右キー : 1 左キー -1 無入力0
*/
float CInputKeyboard::GetAxisHorizontal(void)
{
	return IsKeyPress(DIK_D) ? 1.0f : IsKeyPress(DIK_A) ? -1.0f : 0.0f;
}

/**
*	キーデータ保存処理
*	@param	void
*	@return	void
*/
void CInputKeyboard::SaveKeyState(void)
{
	// キー情報セーブ中じゃなかったら何もせず終了
	if (m_keyStateMode != KEYSTATE_MODE_SAVE)
		return;

	// 現在のキー情報をバッファに保存
	memcpy((m_pFileKeyState + (m_cntFrame * 256)), m_aKeyState, sizeof(m_aKeyState));
	memcpy((m_pFileKeyStateTrigger + (m_cntFrame * 256)), m_aKeyStateTrigger, sizeof(m_aKeyStateTrigger));
	memcpy((m_pFileKeyStateRelease + (m_cntFrame * 256)), m_aKeyStateRelease, sizeof(m_aKeyStateRelease));
	memcpy((m_pFileKeyStateRepeat + (m_cntFrame * 256)), m_aKeyStateRepeat, sizeof(m_aKeyStateRepeat));

	// キー情報保存フレームをカウント
	m_cntFrame++;

	// セーブ最大フレームまでいったら、セーブ終了
	if (m_cntFrame >= SAVE_FRAME)
	{
		EndSaveKeyState();
	}
}

/**
*	キーデータ保存開始
*	@param	void
*	@return	TRUE : 保存開始成功
*	@return	FALSE: 保存開始失敗
*/
bool CInputKeyboard::StartSaveKeyState(void)
{
	// すでにセーブ・ロード処理中だったら、セーブ開始失敗
	if (m_keyStateMode != KEYSTATE_MODE_NONE)
		return false;

	// セーブ用ワークを生成
	m_pFileKeyState = new BYTE[SAVE_FRAME * 256];
	m_pFileKeyStateTrigger = new BYTE[SAVE_FRAME * 256];
	m_pFileKeyStateRelease = new BYTE[SAVE_FRAME * 256];
	m_pFileKeyStateRepeat = new BYTE[SAVE_FRAME * 256];

	// ワークのクリア
	memset(m_pFileKeyState, 0, sizeof(BYTE) * SAVE_FRAME * 256);
	memset(m_pFileKeyStateTrigger, 0, sizeof(BYTE) * SAVE_FRAME * 256);
	memset(m_pFileKeyStateRelease, 0, sizeof(BYTE) * SAVE_FRAME * 256);
	memset(m_pFileKeyStateRepeat, 0, sizeof(BYTE) * SAVE_FRAME * 256);

	// 保存用フレームカウンタを初期化
	m_cntFrame = 0;

	// キー情報をセーブ中に設定
	m_keyStateMode = KEYSTATE_MODE_SAVE;

	return true;
}

/**
*	キーデータ保存終了
*	@param	void
*	@return	TRUE : 保存終了成功
*	@return	FALSE: 保存終了失敗
*/
bool CInputKeyboard::EndSaveKeyState(void)
{
	// セーブ中じゃなければ何もせず終了
	if (m_keyStateMode != KEYSTATE_MODE_SAVE)
		return false;

	// データを出力するファイルをオープン（追加書き込み）
	FILE* fp;
	fp = fopen("Resources/DEMODATA/GameDemo000.dat", "wb");

	// ファイルオープンのエラー処理
	if (fp == NULL)
	{
		MessageBox(NULL,
			L"キーデータ保存用ファイルがありませんでした。",
			L"CInputKeyboard.cpp",
			MB_OK);

		return false;
	}

	// 保存したキーデータをファイル書き込み
	fwrite(m_pFileKeyState, (int)sizeof(BYTE) * SAVE_FRAME * 256, 1, fp);
	fwrite(m_pFileKeyStateTrigger, (int)sizeof(BYTE) * SAVE_FRAME * 256, 1, fp);
	fwrite(m_pFileKeyStateRelease, (int)sizeof(BYTE) * SAVE_FRAME * 256, 1, fp);
	fwrite(m_pFileKeyStateRepeat, (int)sizeof(BYTE) * SAVE_FRAME * 256, 1, fp);

	// ファイルクローズ
	fclose(fp);

	// 保存用バッファの解放
	if (m_pFileKeyState != NULL)
	{
		delete[] m_pFileKeyState;
		m_pFileKeyState = NULL;
	}
	if (m_pFileKeyStateTrigger != NULL)
	{
		delete[] m_pFileKeyStateTrigger;
		m_pFileKeyStateTrigger = NULL;
	}
	if (m_pFileKeyStateRelease != NULL)
	{
		delete[] m_pFileKeyStateRelease;
		m_pFileKeyStateRelease = NULL;
	}
	if (m_pFileKeyState != NULL)
	{
		delete[] m_pFileKeyStateRepeat;
		m_pFileKeyStateRepeat = NULL;
	}

	// キー情報セーブ設定を解除
	m_keyStateMode = KEYSTATE_MODE_NONE;

	// 保存終了成功
	return true;
}

/**
*	キーデータ読み込み開始
*	@param	void
*	@return	TRUE : 読み込み開始成功
*	@return	FALSE: 読み込み開始失敗
*/
bool CInputKeyboard::StartLoadKeyState(void)
{
	m_cntFrame = 0;							// フレームカウンタ
	m_pFileKeyState = NULL;					// セーブ・ロード用キー情報ワーク
	m_pFileKeyStateTrigger = NULL;			// セーブ・ロード用キートリガー情報ワーク
	m_pFileKeyStateRelease = NULL;			// セーブ・ロード用キーリリース情報ワーク
	m_pFileKeyStateRepeat = NULL;			// セーブ・ロード用キーリピート情報ワーク
	m_keyStateMode = KEYSTATE_MODE_NONE;	// キー情報のセーブ・ロード状態

	// すでにロード・セーブ中だったら、ロード開始失敗
	if (m_keyStateMode != KEYSTATE_MODE_NONE)
		return false;

	// ロード用ワークを生成
	m_pFileKeyState = new BYTE[SAVE_FRAME * 256];
	m_pFileKeyStateTrigger = new BYTE[SAVE_FRAME * 256];
	m_pFileKeyStateRelease = new BYTE[SAVE_FRAME * 256];
	m_pFileKeyStateRepeat = new BYTE[SAVE_FRAME * 256];

	// ワークのクリア
	memset(m_pFileKeyState, 0, sizeof(BYTE) * SAVE_FRAME * 256);
	memset(m_pFileKeyStateTrigger, 0, sizeof(BYTE) * SAVE_FRAME * 256);
	memset(m_pFileKeyStateRelease, 0, sizeof(BYTE) * SAVE_FRAME * 256);
	memset(m_pFileKeyStateRepeat, 0, sizeof(BYTE) * SAVE_FRAME * 256);

	// ロード用フレームカウンタを初期化
	m_cntFrame = 0;

	// キー情報をロード中に設定
	m_keyStateMode = KEYSTATE_MODE_LOAD;

	// データを出力するファイルをオープン（追加書き込み）
	FILE* fp;
	fp = fopen("Resources/DEMODATA/GameDemo000.dat", "rb");

	// ファイルオープンのエラー処理
	if (fp == NULL)
	{
		MessageBox(NULL,
			L"キーデータ読み込み用ファイルがオープンできませんでした。",
			L"CInputKeyboard.cpp",
			MB_OK);

		return false;
	}

	// 保存したキーデータをファイル書き込み
	fread(m_pFileKeyState, (int)sizeof(BYTE) * SAVE_FRAME * 256, 1, fp);
	fread(m_pFileKeyStateTrigger, (int)sizeof(BYTE) * SAVE_FRAME * 256, 1, fp);
	fread(m_pFileKeyStateRelease, (int)sizeof(BYTE) * SAVE_FRAME * 256, 1, fp);
	fread(m_pFileKeyStateRepeat, (int)sizeof(BYTE) * SAVE_FRAME * 256, 1, fp);

	// ファイルクローズ
	fclose(fp);

	return true;
}

/**
*	キーデータ読み込み終了
*	@param	void
*	@return	TRUE : 読み込み終了成功
*	@return	FALSE: 読み込み終了失敗
*/
bool CInputKeyboard::EndLoadKeyState(void)
{
	// キー情報をロード中じゃなければ、何もせずに終了
	if (m_keyStateMode != KEYSTATE_MODE_LOAD)
	{
		return false;
	}

	// 保存用バッファの解放
	if (m_pFileKeyState != NULL)
	{
		delete[] m_pFileKeyState;
		m_pFileKeyState = NULL;
	}
	if (m_pFileKeyStateTrigger != NULL)
	{
		delete[] m_pFileKeyStateTrigger;
		m_pFileKeyStateTrigger = NULL;
	}
	if (m_pFileKeyStateRelease != NULL)
	{
		delete[] m_pFileKeyStateRelease;
		m_pFileKeyStateRelease = NULL;
	}
	if (m_pFileKeyStateRepeat != NULL)
	{
		delete[] m_pFileKeyStateRepeat;
		m_pFileKeyStateRepeat = NULL;
	}

	// キー情報ロードを解除
	m_keyStateMode = KEYSTATE_MODE_NONE;

	// 読み込み終了成功
	return true;
}

/**
*	キーデータ読み込み処理
*	@param	void
*	@return	void
*/
void CInputKeyboard::LoadKeyState(void)
{
	// キー情報をロード中じゃなければ、何もせず終了
	if (m_keyStateMode != KEYSTATE_MODE_LOAD)
	{
		return;
	}

	// キー情報保存フレームをカウント
	m_cntFrame++;

	// セーブ最大フレームまでいったら、セーブ終了
	if (m_cntFrame >= SAVE_FRAME)
	{
		EndLoadKeyState();
	}
}