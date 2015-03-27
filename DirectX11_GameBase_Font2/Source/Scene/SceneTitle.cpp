//==============================================================================
// File		SceneTitle.cpp
// Comment	タイトル画面クラス
// Author	TOMOHIRO KOUNO
// Create	2014年7月10日
//==============================================================================

//------------------------------------------------------------------------------
//	インクルード
//------------------------------------------------------------------------------
#include "SceneTitle.h"

// Sprite
#include "Sprite/Sprite.h"

// Input
#include "Input/InputKeyboard.h"

// System
#include "System/SystemManager.h"

//------------------------------------------------------------------------------
//	定数
//------------------------------------------------------------------------------
namespace ns_TitleConstant
{
	
};

/**
* @brief Constructor
* @param	void
* @return	void
*/
CSceneTitle::CSceneTitle(void)
{
	CSprite::PARAM param = {XMFLOAT2(0,0),0.0f,L"Resources/Texture/BlockTexture.png"};
	using namespace ns_TitleConstant;
	m_pBG = new CSprite(param);
	m_pBG->SetWidth(ns_ConstantTable::SCREEN_WIDTH);
	m_pBG->SetHeight(ns_ConstantTable::SCREEN_HEIGHT);
	m_pBG->SetPolygonAlign(CSprite::ALIGN_LEFT_TOP);
}

/**
* @brief Destructor
*/
CSceneTitle::~CSceneTitle(void)
{
	SafeDelete(m_pBG);
}

/**
*	更新
*	@param	void
*	@return	void
*/
void CSceneTitle::Update(void)
{
	using namespace ns_TitleConstant;

	CInputKeyboard* input_keyboard = GETINPUTKEYBOARD;

	if(input_keyboard->IsKeyTrigger(DIK_RETURN))
	{
		CSceneManager* scene_manager = GETSCENEMANAGER;
		scene_manager->GotoScene(CSceneManager::SCENE_TYPE_GAME);
	}
	m_pBG->Update();
}

/**
*	描画
*	@param	void
*	@return	void
*/
void CSceneTitle::Draw(void)
{
	m_pBG->Draw();
}