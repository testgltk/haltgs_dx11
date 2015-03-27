//==============================================================================
// File		SystemManager.h
// Comment	�����V�X�e���Ǘ��N���X
// Author	TOMOHIRO KOUNO
// Create	2014�N6��15��
//==============================================================================

//------------------------------------------------------------------------------
//	�C���N���[�h�K�[�h
//------------------------------------------------------------------------------
#pragma once
#ifndef _SYSTEMMANAGER_H_
#define _SYSTEMMANAGER_H_

//------------------------------------------------------------------------------
//	�O���錾
//------------------------------------------------------------------------------
class ISystem;
class CInputKeyboard;
class CInputMouse;
class CRenderer;
class CSceneManager;

//------------------------------------------------------------------------------
//	�N���X��`
//------------------------------------------------------------------------------
class CSystemManager
{
public:
	CSystemManager(void);

	~CSystemManager(void);

	void EntrySystem(ISystem* pSystem);

	void Update(void);
	void Draw(void);
	void Finalize(void);

	CInputKeyboard* GetKeyboard(void){ return m_pKeyboard; }
	CInputMouse*	GetMouse(void){ return m_pMouse; }

	ID3D11Device* GetDevice(void);
	ID3D11DeviceContext* GetDeviceContext(void);

	/**
	*	�C���X�^���X�擾����
	*	@param	void
	*	@return �C���X�^���X�|�C���^
	*/
	static CSystemManager* GetInstance(void);

private:
	static const int MAX_SYSTEM = 20;
	ISystem* m_pSystems[MAX_SYSTEM];
	int SystemCount;

	CInputKeyboard* m_pKeyboard;
	CInputMouse*	m_pMouse;
	CRenderer*		m_pRenderer;
	CSceneManager*	m_pSceneManager;
	static CSystemManager* m_pInstance;
};


#define GETDEVICE			 CSystemManager::GetInstance()->GetDevice();
#define GETDEVICECONTEXT	 CSystemManager::GetInstance()->GetDeviceContext();
#endif