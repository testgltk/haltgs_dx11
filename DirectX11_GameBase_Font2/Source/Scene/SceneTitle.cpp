//==============================================================================
// File		SceneTitle.cpp
// Comment	�^�C�g����ʃN���X
// Author	TOMOHIRO KOUNO
// Create	2014�N7��10��
//==============================================================================

//------------------------------------------------------------------------------
//	�C���N���[�h
//------------------------------------------------------------------------------
#include "SceneTitle.h"
#include "Sprite/Sprite.h"

//------------------------------------------------------------------------------
//	�萔
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
	CSprite::PARAM bg_param = {XMFLOAT2(0,0),0.0f,L"Resources/Texture/TITLEBG2.png"};
	CSprite::PARAM pe_param = {XMFLOAT2(ns_ConstantTable::SCREEN_WIDTH * 0.5f,ns_ConstantTable::SCREEN_HEIGHT - 100.0f),0.0f,L"Resources/Texture/PUSHENTER.png"};
	using namespace ns_TitleConstant;
	m_pBG = new CSprite(bg_param);
	m_pBG->SetWidth(ns_ConstantTable::SCREEN_WIDTH);
	m_pBG->SetHeight(ns_ConstantTable::SCREEN_HEIGHT);
	m_pBG->SetPolygonAlign(CSprite::ALIGN_LEFT_TOP);

	m_pPushEnter = new CSprite(pe_param);
}

/**
* @brief Destructor
*/
CSceneTitle::~CSceneTitle(void)
{
	SafeDelete(m_pBG);
	SafeDelete(m_pPushEnter);
}

/**
*	�X�V
*	@param	void
*	@return	void
*/
void CSceneTitle::Update(void)
{
	using namespace ns_TitleConstant;

	m_pBG->Update();
	m_pPushEnter->Update();
}

/**
*	�`��
*	@param	void
*	@return	void
*/
void CSceneTitle::Draw(void)
{
	m_pBG->Draw();
	m_pPushEnter->Draw();
}