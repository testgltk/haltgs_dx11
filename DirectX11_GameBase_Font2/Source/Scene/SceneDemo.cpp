//==============================================================================
// File		SceneDemo.cpp
// Comment	ロゴ画面クラス
// Author	TOMOHIRO KOUNO
// Create	2014年7月10日
//==============================================================================

//------------------------------------------------------------------------------
//	インクルード
//------------------------------------------------------------------------------
#include "SceneDemo.h"

//------------------------------------------------------------------------------
//	定数
//------------------------------------------------------------------------------
namespace ns_DemoConstant
{

};

/**
* @brief Constructor
* @param	void
* @return	void
*/
CSceneDemo::CSceneDemo(void)
{
	using namespace ns_DemoConstant;

	
	//デモ開始
#if 1
	//CManager::GetXInput()->SetKeyStateMode(CInputXInput::KEYSTATE_MODE_LOAD);
	//CManager::GetKeyboard()->StartLoadKeyState();
#else
	//録画開始
	CManager::GetKeyboard()->StartSaveKeyState();

#endif
}

/**
* @brief Destructor
*/
CSceneDemo::~CSceneDemo(void)
{
	

	//デモ終了
#if 1
	//CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	//CManager::GetXInput()->SetKeyStateMode(CInputXInput::KEYSTATE_MODE_NONE);
	//pKeyboard->EndLoadKeyState();
#else
	//録画終了
	//CManager::GetKeyboard()->EndSaveKeyState();
#endif
}

/**
*	更新
*	@param	void
*	@return	void
*/
void CSceneDemo::Update(void)
{
	
	//更新
	UpdateExec();

}

/**
*	描画
*	@param	void
*	@return	void
*/
void CSceneDemo::Draw(void)
{
	//描画
	DrawExec();
}

void CSceneDemo::CreateDatas(void)
{
	using namespace ns_DemoConstant;
	
	
}

void CSceneDemo::DestroyDatas(void)
{
	DestroyObjectManager();
	
}

void CSceneDemo::CreateObjectManager(void)
{
	
}

void CSceneDemo::DestroyObjectManager(void)
{

}

void CSceneDemo::UpdateExec(void)
{
	
}
void CSceneDemo::DrawExec(void)
{
	
}