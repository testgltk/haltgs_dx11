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
#include "Sprite/Sprite.h"

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