//==============================================================================
// File		InputXInput.h
// Comment	XInputクラス
// Author	TOMOHIRO KOUNO
// Create	2014年12月20日
//==============================================================================

//------------------------------------------------------------------------------
//	インクルード
//------------------------------------------------------------------------------
#include "Input/InputXInput.h"

//------------------------------------------------------------------------------
// メソッド定義
//------------------------------------------------------------------------------
CInputXInput::CInputXInput()
{
	// XInput有効にする
	XInputEnable(TRUE);


	// 初期化
	ZeroMemory(&m_bRStickIsPress, sizeof(m_bRStickIsPress));
	for (DWORD i = 0; i< PAD_NUM; i++)
	{
		ZeroMemory(&m_sPadState[i].xPadState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_sPadStateOld[i].xPadState, sizeof(XINPUT_STATE));
		m_sPadState[i].isConnect = false;
		m_sPadStateOld[i].isConnect = false;
		m_nRepeatStartTime[i] = 40;
		m_nRepeatSleepTime[i] = 10;
	}

	m_InputVTKey[VT_INPUT_LEFT]			= XINPUT_GAMEPAD_DPAD_LEFT;
	m_InputVTKey[VT_INPUT_RIGHT]		= XINPUT_GAMEPAD_DPAD_RIGHT;
	m_InputVTKey[VT_INPUT_UP]			= XINPUT_GAMEPAD_DPAD_UP;
	m_InputVTKey[VT_INPUT_DOWN]			= XINPUT_GAMEPAD_DPAD_DOWN;
	m_InputVTKey[VT_INPUT_R_LEFT]		= VK_PAD_LTHUMB_LEFT;
	m_InputVTKey[VT_INPUT_R_RIGHT]		= VK_PAD_LTHUMB_RIGHT;
	m_InputVTKey[VT_INPUT_R_UP]			= VK_PAD_LTHUMB_UP;
	m_InputVTKey[VT_INPUT_R_DOWN]		= VK_PAD_LTHUMB_DOWN;
	m_InputVTKey[VT_INPUT_Y_OR_DELTA]	= XINPUT_GAMEPAD_X;
	m_InputVTKey[VT_INPUT_B_OR_CIRCLE]	= XINPUT_GAMEPAD_A;
	m_InputVTKey[VT_INPUT_A_OR_X]		= XINPUT_GAMEPAD_B;
	m_InputVTKey[VT_INPUT_X_OR_RECT]	= XINPUT_GAMEPAD_Y;
	m_InputVTKey[VT_INPUT_5]			= XINPUT_GAMEPAD_LEFT_SHOULDER;
	m_InputVTKey[VT_INPUT_6]			= XINPUT_GAMEPAD_RIGHT_SHOULDER;
	m_InputVTKey[VT_INPUT_7]			= XINPUT_GAMEPAD_LEFT_THUMB;
	m_InputVTKey[VT_INPUT_8]			= XINPUT_GAMEPAD_RIGHT_THUMB;
	m_InputVTKey[VT_INPUT_9]			= XINPUT_GAMEPAD_START;
	m_InputVTKey[VT_INPUT_10]			= XINPUT_GAMEPAD_BACK;

	m_KeyStateMode = KEYSTATE_MODE_NONE;
}

CInputXInput::~CInputXInput()
{
	// XInput無効にする
	XInputEnable(FALSE);
}

void CInputXInput::Release(void)
{
	delete this;
}

bool CInputXInput::GetEnableDevise(void)
{
	XINPUT_CAPABILITIES sStatus;
	for (int i = 0; i<PAD_NUM; i++)
	{
		DWORD ret = XInputGetCapabilities(i, XINPUT_FLAG_GAMEPAD, &sStatus);

		// デバイスを発見
		if (ret == ERROR_SUCCESS)
		{
			return true;
		}
	}
	return false;
}

void CInputXInput::Update(void)
{


	ZeroMemory(&m_bRStickIsPress, sizeof(m_bRStickIsPress));


	for (int i = 0; i< PAD_NUM; i++)
	{
		// 前のデータ取得
		memcpy(&m_sPadStateOld[i].xPadState, &m_sPadState[i].xPadState, sizeof(XINPUT_STATE));

		// 初期化
		ZeroMemory(&m_sPadState[i].xPadState, sizeof(XINPUT_STATE));

		// ステータス取得
		DWORD dwResult = XInputGetState(i, &m_sPadState[i].xPadState);

		if (dwResult == ERROR_SUCCESS)
		{
			m_sPadState[i].isConnect = true;

			//左
			if (m_sPadState[i].xPadState.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			{
				m_sPadState[i].xPadState.Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_RIGHT;
			}
			if (m_sPadState[i].xPadState.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			{
				m_sPadState[i].xPadState.Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_LEFT;
			}
			if (m_sPadState[i].xPadState.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			{
				m_sPadState[i].xPadState.Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_UP;
			}
			if (m_sPadState[i].xPadState.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
			{
				m_sPadState[i].xPadState.Gamepad.wButtons |= XINPUT_GAMEPAD_DPAD_DOWN;
			}

			//右
			if (m_sPadState[i].xPadState.Gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
			{
				m_bRStickIsPress[RSTICK_BUTTON_RIGHT][i] = true;
			}
			if (m_sPadState[i].xPadState.Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
			{
				m_bRStickIsPress[RSTICK_BUTTON_LEFT][i] = true;
			}
			if (m_sPadState[i].xPadState.Gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
			{
				m_bRStickIsPress[RSTICK_BUTTON_UP][i] = true;

			}
			if (m_sPadState[i].xPadState.Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE)
			{
				m_bRStickIsPress[RSTICK_BUTTON_DONW][i] = true;
			}
		}
		else
		{
			m_sPadState[i].isConnect = false;
		}
	}
	
	// リピートデータ作成
	for (int nPad = 0; nPad < PAD_NUM; nPad++)
	{
		for (int i = 0; i<VT_INPUT_MAX; ++i)
		{
			m_InputRepeatBuff[i][nPad] = (m_InputRepeatBuff[i][nPad] * (int)IsPress((VT_INPUT)i, nPad)) + 1;
			if (m_InputRepeatBuff[i][nPad] / m_nRepeatStartTime[nPad] >= 1)
			{
				m_InputRepeatBuff[i][nPad] -= (BYTE)m_nRepeatSleepTime[nPad];
			}
		}
	}
}

 bool CInputXInput::IsPress(VT_INPUT vk,int nPadID)
{
	 //デモが再生中の場合はキーボード入力を外部が行ってるため終了
	 if (m_KeyStateMode == KEYSTATE_MODE_LOAD)
	 {
		 return false;
	 }

	 if (!m_sPadState[nPadID].isConnect)
	 {
		 return false;
	 }

	const WORD padButtonBit = m_sPadState[nPadID].xPadState.Gamepad.wButtons;
	return (padButtonBit & m_InputVTKey[vk]) ? true : false;
}

bool CInputXInput::IsTrigger(VT_INPUT vk, int nPadID)
{
	//デモが再生中の場合はキーボード入力を外部が行ってるため終了
	if (m_KeyStateMode == KEYSTATE_MODE_LOAD)
	{
		return false;
	}

	if (!m_sPadState[nPadID].isConnect)
	{
		return false;
	}

	const WORD padButtonBit = m_sPadState[nPadID].xPadState.Gamepad.wButtons;
	const WORD padButtonBitOld = m_sPadStateOld[nPadID].xPadState.Gamepad.wButtons;

	return (((padButtonBit ^ padButtonBitOld) & padButtonBit) & m_InputVTKey[vk]) ? true : false;
}

inline bool CInputXInput::IsRelease(VT_INPUT vk,int nPadID)
{
	//デモが再生中の場合はキーボード入力を外部が行ってるため終了
	if (m_KeyStateMode == KEYSTATE_MODE_LOAD)
	{
		return false;
	}

	if (!m_sPadState[nPadID].isConnect)
	{
		return false;
	}

	const WORD padButtonBit = m_sPadState[nPadID].xPadState.Gamepad.wButtons;
	const WORD padButtonBitOld = m_sPadStateOld[nPadID].xPadState.Gamepad.wButtons;

	return (((padButtonBit ^ padButtonBitOld) & ~padButtonBit) & m_InputVTKey[vk]) ? true : false;
}

bool CInputXInput::IsRepeat(VT_INPUT vk,int nPadID)
{
	//デモが再生中の場合はキーボード入力を外部が行ってるため終了
	if (m_KeyStateMode == KEYSTATE_MODE_LOAD)
	{
		return false;
	}

	if (!m_sPadState[nPadID].isConnect)
	{
		return false;
	}	
	return IsTrigger(vk,nPadID) ? true : (m_InputRepeatBuff[vk][nPadID] >= (m_nRepeatStartTime[nPadID] - 1));
}

bool CInputXInput::IsTriggerDemo(VT_INPUT vk, int nPadID)
{
	if (!m_sPadState[nPadID].isConnect)
	{
		return false;
	}

	const WORD padButtonBit = m_sPadState[nPadID].xPadState.Gamepad.wButtons;
	const WORD padButtonBitOld = m_sPadStateOld[nPadID].xPadState.Gamepad.wButtons;

	return (((padButtonBit ^ padButtonBitOld) & padButtonBit) & m_InputVTKey[vk]) ? true : false;
}

void CInputXInput::Shake(float left, float right,int nPadID)
{
	if (left < 0)
	{
		left = 0;
	}
	else if (left > 1)
	{
		left = 1;
	}

	if (right < 0)
	{
		right = 0;
	}
	else if (right > 1)
	{
		right = 1;
	}

	XINPUT_VIBRATION set = { (WORD)left * 65535, (WORD)right * 65535 };

	if (m_sPadState[nPadID].isConnect)
	{
		XInputSetState(nPadID, &set);
	}
}

/**
*	上下に該当するキーが押された
*	@param	void
*	@return	上キー : 1 下キー -1 無入力0
*/
float CInputXInput::GetAxisVertical(void)
{
	//デモが再生中の場合はキーボード入力を外部が行ってるため終了
	if (m_KeyStateMode == KEYSTATE_MODE_LOAD)
	{
		return false;
	}

	return IsPress(VT_INPUT_UP, 0) ? 1.0f : IsPress(VT_INPUT_DOWN, 0) ? -1.0f : 0.0f;
}

/**
*	左右に該当するキーが押された
*	@param	void
*	@return	右キー : 1 左キー -1 無入力0
*/
float CInputXInput::GetAxisHorizontal(void)
{
	//デモが再生中の場合はキーボード入力を外部が行ってるため終了
	if (m_KeyStateMode == KEYSTATE_MODE_LOAD)
	{
		return false;
	}
	return IsPress(VT_INPUT_RIGHT, 0) ? 1.0f : IsPress(VT_INPUT_LEFT, 0) ? -1.0f : 0.0f;
}

bool CInputXInput::IsRStickPress(RSTICK_BUTTON Button, int nPadID)
{
	//デモが再生中の場合はキーボード入力を外部が行ってるため終了
	if (m_KeyStateMode == KEYSTATE_MODE_LOAD)
	{
		return false;
	}

	return m_bRStickIsPress[Button][nPadID];
};

void CInputXInput::SetKeyStateMode(KEYSTATE_MODE KeyStateMode)
{
	m_KeyStateMode = KeyStateMode;
}