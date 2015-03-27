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
#include "System/SystemManager.h"
#include "Sprite/Sprite.h"
#include "Input/InputMouse.h"
#include "SceneManager.h"

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
CSceneTitle::CSceneTitle(void) :
m_pBackground(nullptr)
	
{
	using namespace ns_TitleConstant;
	using namespace ns_ConstantTable;


	const CSprite::PARAM param1 = { XMFLOAT2(SCREEN_WIDTH  * 0.5f, SCREEN_HEIGHT* 0.5f), 0.0f, L"Resources/Texture/BlockTexture.png" };
	m_pBackground = new CSprite(param1);
	m_pBackground->SetWidth(SCREEN_WIDTH);
	m_pBackground->SetHeight(SCREEN_HEIGHT);
}

/**
* @brief Destructor
*/
CSceneTitle::~CSceneTitle(void)
{
	//SafeDelete(m_pBackground);
}

/**
*	更新
*	@param	void
*	@return	void
*/
void CSceneTitle::Update(void)
{
	using namespace ns_TitleConstant;

	// 入力で遷移
	CInputKeyboard *pKey = GETINPUTKEYBOARD;
	CInputMouse* pMs = GETINPUTMOUSE;

	if(pKey->IsKeyTrigger(DIK_RETURN) ||
		pMs->IsLeftPress())
	{
		CSceneManager *pSm = GETSCENEMANAGER;
		pSm->GotoScene(CSceneManager::SCENE_TYPE_GAME);
	}

	m_pBackground->Update();
}

/**
*	描画
*	@param	void
*	@return	void
*/
void CSceneTitle::Draw(void)
{
	m_pBackground->Draw();
}