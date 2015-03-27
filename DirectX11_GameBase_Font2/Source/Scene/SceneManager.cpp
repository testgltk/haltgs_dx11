//==============================================================================
// File		SceneManager.cpp
// Comment	シーン管理クラス
// Author	TOMOHIRO KOUNO
// Create	2014年7月11日
//==============================================================================

//------------------------------------------------------------------------------
//	インクルード
//------------------------------------------------------------------------------
#include "SceneManager.h"
#include "SceneGame.h"
#include "SceneTitle.h"
#include "SceneDebug.h"
#include "SceneLogo.h"
#include "SceneResult.h"
#include "SceneRanking.h"
#include "SceneDemo.h"
#include "Fade/Fade.h"

CSceneManager::CSceneManager(void)
	:m_pScene(nullptr)
	, m_pSceneNext(nullptr)
	, m_bReloadScene(false)
{
	m_SceneType			= SCENE_TYPE_LOGO;
	m_SceneTypeNext		= SCENE_TYPE_LOGO;
	m_pScene			= new CSceneLogo();
}

CSceneManager::~CSceneManager(void)
{
	SafeDelete(m_pScene);
}

void CSceneManager::Finalize(void)
{
}

void CSceneManager::Update(void)
{
	m_pScene->Update();
}

void CSceneManager::Draw(void)
{
	m_pScene->Draw();
}

void CSceneManager::ReloadScene(void)
{
	m_bReloadScene = true;
}

void CSceneManager::GotoScene(SCENE_TYPE Type)
{
	m_SceneTypeNext = Type;
}

void CSceneManager::Change(void)
{
	if( m_SceneType == m_SceneTypeNext 
	&& !m_bReloadScene)
	{
		return;
	}

	m_SceneType = m_SceneTypeNext;

	delete m_pScene;
	m_pScene = nullptr;

	switch(m_SceneTypeNext)
	{
		case SCENE_TYPE_LOGO	: m_pScene = new CSceneLogo();	break;
		case SCENE_TYPE_TITLE	: m_pScene = new CSceneTitle();	break;
		case SCENE_TYPE_DEMO	: m_pScene = new CSceneDemo();	break;
		case SCENE_TYPE_GAME	: m_pScene = new CSceneGame();	break;
		case SCENE_TYPE_RESULT	: m_pScene = new CSceneResult();break;
		case SCENE_TYPE_RANKING	: m_pScene = new CSceneRanking();break;
		case SCENE_TYPE_GAMEOVER: m_pScene = new CSceneGameOver();break;
	}

	m_bReloadScene = false;
}

CSceneBase* CSceneManager::GetCurrentScene(void)
{
	return m_pScene;
}

CSceneManager::SCENE_TYPE CSceneManager::GetCurrentSceneType(void)
{
	return m_SceneType;
}