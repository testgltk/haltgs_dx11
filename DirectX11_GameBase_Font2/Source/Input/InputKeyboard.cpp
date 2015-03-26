//==============================================================================
// File		InputKeyboard.cpp
// Comment	�L�[�{�[�h���̓N���X
// Author	TOMOHIRO KOUNO
// Create	2014�N6��27��
//==============================================================================

//------------------------------------------------------------------------------
//	�C���N���[�h
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
	// �e���[�N�̃N���A
	ClearState();
}

/**
* @brief Destructor
*/
CInputKeyboard::~CInputKeyboard()
{
	// �e���[�N�̃N���A
	ClearState();
}

/**
*	Init Input Device
*	@param	hInst �n���h���C���X�^���X
*	@param	hWnd  �n���h���E�B���h�E
*	@return	�������ɐ���������?
*/
HRESULT CInputKeyboard::Initialize(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	// ���͏����̏�����
	CInput::Initialize(hInst, hWnd);

	

	// �f�o�C�X�I�u�W�F�N�g���쐬
	hr = _pDInput->CreateDevice(GUID_SysKeyboard, &_pDIDevice, nullptr);
	if(FAILED(hr) || _pDIDevice == nullptr)
	{
		MessageBox(hWnd, L"�L�[�{�[�h������܂���I", L"�x���I", MB_ICONWARNING);
		return hr;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	hr = _pDIDevice->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr))
	{
		MessageBox(hWnd, L"�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", L"�x���I", MB_ICONWARNING);
		return hr;
	}

	// �������[�h�ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = _pDIDevice->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(hr))
	{
		MessageBox(hWnd, L"�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", L"�x���I", MB_ICONWARNING);
		return hr;
	}

	//�A�N�Z�X�����l��(���͐���J�n)
	_pDIDevice->Acquire();

	// �L�[���Z�[�u�E���[�h�Ɋւ��鏉����
	m_cntFrame = 0;							// �t���[���J�E���^
	m_pFileKeyState = NULL;					// �Z�[�u�E���[�h�p�L�[��񃏁[�N
	m_pFileKeyStateTrigger = NULL;			// �Z�[�u�E���[�h�p�L�[�g���K�[��񃏁[�N
	m_pFileKeyStateRelease = NULL;			// �Z�[�u�E���[�h�p�L�[�����[�X��񃏁[�N
	m_pFileKeyStateRepeat = NULL;			// �Z�[�u�E���[�h�p�L�[���s�[�g��񃏁[�N
	m_keyStateMode = KEYSTATE_MODE_NONE;	// �L�[���̃Z�[�u�E���[�h���
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
	// ���͏����̊J��
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

	// �L�[�������[�h����������
	if (m_keyStateMode == KEYSTATE_MODE_LOAD)
	{
		// ���[�h���̏������s��
		LoadKeyState();
	}

	hr = _pDIDevice->GetDeviceState(sizeof(aKeyState), aKeyState);

	///*// �L�[�������[�h����������
	//if(m_keyStateMode == KEYSTATE_MODE_LOAD)
	//{
	//// �O���t�@�C������f�[�^���擾
	//LoadKeyState();
	//hr = S_OK;
	//}
	//// �L�[�������[�h������Ȃ�������
	//else
	//{
	//// �f�o�C�X����f�[�^���擾
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
		//�L�[�N���A ���X�g���̌���͂����
		ClearState();
		_pDIDevice->Acquire();
	}

	// �L�[���Z�[�u����������
	if (m_keyStateMode == KEYSTATE_MODE_SAVE)
	{
		// �L�[�X�e�[�g�f�[�^�̕ۑ�
		SaveKeyState();
	}

	return;
}

/**
*	�L�[�����������Ă邩�H
*	@param	nKey �L�[�ԍ�
*	@return	BOOL ������Ă邩�ǂ���
*/
BOOL CInputKeyboard::IsKeyPress(int nKey)
{
	//return (m_aKeyState[nKey] & 0x80) ? TRUE: FALSE;
	if (m_keyStateMode == KEYSTATE_MODE_LOAD)
	{
		// ���[�h�����L�[�����擾
		return (*(m_pFileKeyState + (m_cntFrame * 256) + nKey) & 0x80) ? TRUE : FALSE;
	}
	// ���[�h���Ă��Ȃ��A�܂��̓��[�h��������ꍇ
	else
	{
		// ���݂̃L�[�����擾
		return (m_aKeyState[nKey] & 0x80) ? TRUE : FALSE;
	}
}

/**
*	�L�[���������u�Ԃ��H
*	@param	nKey �L�[�ԍ�
*	@return	BOOL �������u�Ԃ��ǂ���
*/
BOOL CInputKeyboard::IsKeyTrigger(int nKey,bool bIgnore)
{
	//return (m_aKeyStateTrigger[nKey] & 0x80) ? TRUE: FALSE;

	if (m_keyStateMode == KEYSTATE_MODE_LOAD && !bIgnore)
	{
		// ���[�h�����L�[�����擾
		return (*(m_pFileKeyStateTrigger + (m_cntFrame * 256) + nKey) & 0x80) ? TRUE : FALSE;
	}
	// ���[�h���Ă��Ȃ��A�܂��̓��[�h��������ꍇ
	else
	{
		// ���݂̃L�[�����擾
		return (m_aKeyStateTrigger[nKey] & 0x80) ? TRUE : FALSE;
	}
}

/**
*	�L�[�𗣂����u�Ԃ��H
*	@param	nKey �L�[�ԍ�
*	@return	BOOL �������u�Ԃ��ǂ���
*/
BOOL CInputKeyboard::IsKeyRelease(int nKey)
{
	return (m_aKeyStateRelease[nKey] & 0x80) ? TRUE: FALSE;
}

/**
*	�L�[�𗣂����u�Ԃ܂����������Ă邩�H
*	@param	nKey �L�[�ԍ�
*	@return	BOOL �������u�Ԃ܂����������Ă邩�ǂ���
*/
BOOL CInputKeyboard::IsKeyRepeat(int nKey)
{
	return (m_aKeyStateRepeat[nKey] & 0x80) ? TRUE: FALSE;
}

/**
*	�L�[���͂̏���
*	@param	nKey �L�[�ԍ�
*	@return	void
*/
void CInputKeyboard::FlushKeyTrigger(int nKey)
{
	m_aKeyStateTrigger[nKey] = 0;
}

/**
*	�L�[���͔z�񏉊���
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
*	�㉺�ɊY������L�[�������ꂽ
*	@param	void
*	@return	��L�[ : 1 ���L�[ -1 ������0
*/
float CInputKeyboard::GetAxisVertical(void)
{
	return IsKeyPress(DIK_W) ? 1.0f : IsKeyPress(DIK_S) ? -1.0f : 0.0f;
}

/**
*	���E�ɊY������L�[�������ꂽ
*	@param	void
*	@return	�E�L�[ : 1 ���L�[ -1 ������0
*/
float CInputKeyboard::GetAxisHorizontal(void)
{
	return IsKeyPress(DIK_D) ? 1.0f : IsKeyPress(DIK_A) ? -1.0f : 0.0f;
}

/**
*	�L�[�f�[�^�ۑ�����
*	@param	void
*	@return	void
*/
void CInputKeyboard::SaveKeyState(void)
{
	// �L�[���Z�[�u������Ȃ������牽�������I��
	if (m_keyStateMode != KEYSTATE_MODE_SAVE)
		return;

	// ���݂̃L�[�����o�b�t�@�ɕۑ�
	memcpy((m_pFileKeyState + (m_cntFrame * 256)), m_aKeyState, sizeof(m_aKeyState));
	memcpy((m_pFileKeyStateTrigger + (m_cntFrame * 256)), m_aKeyStateTrigger, sizeof(m_aKeyStateTrigger));
	memcpy((m_pFileKeyStateRelease + (m_cntFrame * 256)), m_aKeyStateRelease, sizeof(m_aKeyStateRelease));
	memcpy((m_pFileKeyStateRepeat + (m_cntFrame * 256)), m_aKeyStateRepeat, sizeof(m_aKeyStateRepeat));

	// �L�[���ۑ��t���[�����J�E���g
	m_cntFrame++;

	// �Z�[�u�ő�t���[���܂ł�������A�Z�[�u�I��
	if (m_cntFrame >= SAVE_FRAME)
	{
		EndSaveKeyState();
	}
}

/**
*	�L�[�f�[�^�ۑ��J�n
*	@param	void
*	@return	TRUE : �ۑ��J�n����
*	@return	FALSE: �ۑ��J�n���s
*/
bool CInputKeyboard::StartSaveKeyState(void)
{
	// ���łɃZ�[�u�E���[�h��������������A�Z�[�u�J�n���s
	if (m_keyStateMode != KEYSTATE_MODE_NONE)
		return false;

	// �Z�[�u�p���[�N�𐶐�
	m_pFileKeyState = new BYTE[SAVE_FRAME * 256];
	m_pFileKeyStateTrigger = new BYTE[SAVE_FRAME * 256];
	m_pFileKeyStateRelease = new BYTE[SAVE_FRAME * 256];
	m_pFileKeyStateRepeat = new BYTE[SAVE_FRAME * 256];

	// ���[�N�̃N���A
	memset(m_pFileKeyState, 0, sizeof(BYTE) * SAVE_FRAME * 256);
	memset(m_pFileKeyStateTrigger, 0, sizeof(BYTE) * SAVE_FRAME * 256);
	memset(m_pFileKeyStateRelease, 0, sizeof(BYTE) * SAVE_FRAME * 256);
	memset(m_pFileKeyStateRepeat, 0, sizeof(BYTE) * SAVE_FRAME * 256);

	// �ۑ��p�t���[���J�E���^��������
	m_cntFrame = 0;

	// �L�[�����Z�[�u���ɐݒ�
	m_keyStateMode = KEYSTATE_MODE_SAVE;

	return true;
}

/**
*	�L�[�f�[�^�ۑ��I��
*	@param	void
*	@return	TRUE : �ۑ��I������
*	@return	FALSE: �ۑ��I�����s
*/
bool CInputKeyboard::EndSaveKeyState(void)
{
	// �Z�[�u������Ȃ���Ή��������I��
	if (m_keyStateMode != KEYSTATE_MODE_SAVE)
		return false;

	// �f�[�^���o�͂���t�@�C�����I�[�v���i�ǉ��������݁j
	FILE* fp;
	fp = fopen("Resources/DEMODATA/GameDemo000.dat", "wb");

	// �t�@�C���I�[�v���̃G���[����
	if (fp == NULL)
	{
		MessageBox(NULL,
			L"�L�[�f�[�^�ۑ��p�t�@�C��������܂���ł����B",
			L"CInputKeyboard.cpp",
			MB_OK);

		return false;
	}

	// �ۑ������L�[�f�[�^���t�@�C����������
	fwrite(m_pFileKeyState, (int)sizeof(BYTE) * SAVE_FRAME * 256, 1, fp);
	fwrite(m_pFileKeyStateTrigger, (int)sizeof(BYTE) * SAVE_FRAME * 256, 1, fp);
	fwrite(m_pFileKeyStateRelease, (int)sizeof(BYTE) * SAVE_FRAME * 256, 1, fp);
	fwrite(m_pFileKeyStateRepeat, (int)sizeof(BYTE) * SAVE_FRAME * 256, 1, fp);

	// �t�@�C���N���[�Y
	fclose(fp);

	// �ۑ��p�o�b�t�@�̉��
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

	// �L�[���Z�[�u�ݒ������
	m_keyStateMode = KEYSTATE_MODE_NONE;

	// �ۑ��I������
	return true;
}

/**
*	�L�[�f�[�^�ǂݍ��݊J�n
*	@param	void
*	@return	TRUE : �ǂݍ��݊J�n����
*	@return	FALSE: �ǂݍ��݊J�n���s
*/
bool CInputKeyboard::StartLoadKeyState(void)
{
	m_cntFrame = 0;							// �t���[���J�E���^
	m_pFileKeyState = NULL;					// �Z�[�u�E���[�h�p�L�[��񃏁[�N
	m_pFileKeyStateTrigger = NULL;			// �Z�[�u�E���[�h�p�L�[�g���K�[��񃏁[�N
	m_pFileKeyStateRelease = NULL;			// �Z�[�u�E���[�h�p�L�[�����[�X��񃏁[�N
	m_pFileKeyStateRepeat = NULL;			// �Z�[�u�E���[�h�p�L�[���s�[�g��񃏁[�N
	m_keyStateMode = KEYSTATE_MODE_NONE;	// �L�[���̃Z�[�u�E���[�h���

	// ���łɃ��[�h�E�Z�[�u����������A���[�h�J�n���s
	if (m_keyStateMode != KEYSTATE_MODE_NONE)
		return false;

	// ���[�h�p���[�N�𐶐�
	m_pFileKeyState = new BYTE[SAVE_FRAME * 256];
	m_pFileKeyStateTrigger = new BYTE[SAVE_FRAME * 256];
	m_pFileKeyStateRelease = new BYTE[SAVE_FRAME * 256];
	m_pFileKeyStateRepeat = new BYTE[SAVE_FRAME * 256];

	// ���[�N�̃N���A
	memset(m_pFileKeyState, 0, sizeof(BYTE) * SAVE_FRAME * 256);
	memset(m_pFileKeyStateTrigger, 0, sizeof(BYTE) * SAVE_FRAME * 256);
	memset(m_pFileKeyStateRelease, 0, sizeof(BYTE) * SAVE_FRAME * 256);
	memset(m_pFileKeyStateRepeat, 0, sizeof(BYTE) * SAVE_FRAME * 256);

	// ���[�h�p�t���[���J�E���^��������
	m_cntFrame = 0;

	// �L�[�������[�h���ɐݒ�
	m_keyStateMode = KEYSTATE_MODE_LOAD;

	// �f�[�^���o�͂���t�@�C�����I�[�v���i�ǉ��������݁j
	FILE* fp;
	fp = fopen("Resources/DEMODATA/GameDemo000.dat", "rb");

	// �t�@�C���I�[�v���̃G���[����
	if (fp == NULL)
	{
		MessageBox(NULL,
			L"�L�[�f�[�^�ǂݍ��ݗp�t�@�C�����I�[�v���ł��܂���ł����B",
			L"CInputKeyboard.cpp",
			MB_OK);

		return false;
	}

	// �ۑ������L�[�f�[�^���t�@�C����������
	fread(m_pFileKeyState, (int)sizeof(BYTE) * SAVE_FRAME * 256, 1, fp);
	fread(m_pFileKeyStateTrigger, (int)sizeof(BYTE) * SAVE_FRAME * 256, 1, fp);
	fread(m_pFileKeyStateRelease, (int)sizeof(BYTE) * SAVE_FRAME * 256, 1, fp);
	fread(m_pFileKeyStateRepeat, (int)sizeof(BYTE) * SAVE_FRAME * 256, 1, fp);

	// �t�@�C���N���[�Y
	fclose(fp);

	return true;
}

/**
*	�L�[�f�[�^�ǂݍ��ݏI��
*	@param	void
*	@return	TRUE : �ǂݍ��ݏI������
*	@return	FALSE: �ǂݍ��ݏI�����s
*/
bool CInputKeyboard::EndLoadKeyState(void)
{
	// �L�[�������[�h������Ȃ���΁A���������ɏI��
	if (m_keyStateMode != KEYSTATE_MODE_LOAD)
	{
		return false;
	}

	// �ۑ��p�o�b�t�@�̉��
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

	// �L�[��񃍁[�h������
	m_keyStateMode = KEYSTATE_MODE_NONE;

	// �ǂݍ��ݏI������
	return true;
}

/**
*	�L�[�f�[�^�ǂݍ��ݏ���
*	@param	void
*	@return	void
*/
void CInputKeyboard::LoadKeyState(void)
{
	// �L�[�������[�h������Ȃ���΁A���������I��
	if (m_keyStateMode != KEYSTATE_MODE_LOAD)
	{
		return;
	}

	// �L�[���ۑ��t���[�����J�E���g
	m_cntFrame++;

	// �Z�[�u�ő�t���[���܂ł�������A�Z�[�u�I��
	if (m_cntFrame >= SAVE_FRAME)
	{
		EndLoadKeyState();
	}
}