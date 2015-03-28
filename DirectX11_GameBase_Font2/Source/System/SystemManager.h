//==============================================================================
// File		SystemManager.h
// Comment	内部システム管理クラス
// Author	TOMOHIRO KOUNO
// Create	2014年6月15日
//==============================================================================

//------------------------------------------------------------------------------
//	インクルードガード
//------------------------------------------------------------------------------
#pragma once
#ifndef _SYSTEMMANAGER_H_
#define _SYSTEMMANAGER_H_
#include "Scene/SceneManager.h"

//------------------------------------------------------------------------------
//	前方宣言
//------------------------------------------------------------------------------
class ISystem;
class CInputKeyboard;
class CInputMouse;
class CRenderer;
class CSceneManager;
class CFontString;

//------------------------------------------------------------------------------
//	クラス定義
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
	CFontString*	GetFont(){ return m_pString; }

	ID3D11Device* GetDevice(void);
	ID3D11DeviceContext* GetDeviceContext(void);
	CSceneManager* GetSceneManager(void) { return m_pSceneManager; }

	void setScore(int nSco){ m_snScore = nSco; }
	int getScore(void){ return m_snScore; }

	/**
	*	インスタンス取得処理
	*	@param	void
	*	@return インスタンスポインタ
	*/
	static CSystemManager* GetInstance(void);

private:
	static const int MAX_SYSTEM = 20;
	ISystem* m_pSystems[MAX_SYSTEM];
	int SystemCount;

	CFontString*	m_pString;
	CInputKeyboard* m_pKeyboard;
	CInputMouse*	m_pMouse;
	CRenderer*		m_pRenderer;
	CSceneManager*	m_pSceneManager;
	static int m_snScore;
	static CSystemManager* m_pInstance;
};


#define GETDEVICE			 CSystemManager::GetInstance()->GetDevice();
#define GETDEVICECONTEXT	 CSystemManager::GetInstance()->GetDeviceContext();
#define GETINPUTKEYBOARD	 CSystemManager::GetInstance()->GetKeyboard();
#define GETINPUTMOUSE		 CSystemManager::GetInstance()->GetMouse();
#define GETSCENEMANAGER		 CSystemManager::GetInstance()->GetSceneManager();
#define GETFONT				 CSystemManager::GetInstance()->GetFont();
#endif