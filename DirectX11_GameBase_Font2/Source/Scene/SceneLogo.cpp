//==============================================================================
// File		SceneLogo.cpp
// Comment	ロゴ画面クラス
// Author	TOMOHIRO KOUNO
// Create	2014年7月10日
//==============================================================================

//------------------------------------------------------------------------------
//	インクルード
//------------------------------------------------------------------------------
#include "SceneLogo.h"
#include "System/SystemManager.h"

//------------------------------------------------------------------------------
//	定数
//------------------------------------------------------------------------------
namespace ns_LogoConstant
{

}

/**
* @brief Constructor
* @param	void
* @return	void
*/
CSceneLogo::CSceneLogo(void)
{
	using namespace ns_LogoConstant;

	
}

/**
* @brief Destructor
*/
CSceneLogo::~CSceneLogo(void)
{
	
}

/**
*	更新
*	@param	void
*	@return	void
*/
void CSceneLogo::Update(void)
{
	using namespace ns_LogoConstant;
	CInputKeyboard* input_keyboard = GETINPUTKEYBOARD;

	if(input_keyboard->IsKeyTrigger(DIK_RETURN))
	{
		CSceneManager* scene_manager = GETSCENEMANAGER;
		scene_manager->GotoScene(CSceneManager::SCENE_TYPE_TITLE);
	}

}

/**
*	描画
*	@param	void
*	@return	void
*/
void CSceneLogo::Draw(void)
{

}