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
*	�X�V
*	@param	void
*	@return	void
*/
void CSceneTitle::Update(void)
{
	using namespace ns_TitleConstant;

	m_pBG->Update();
}

/**
*	�`��
*	@param	void
*	@return	void
*/
void CSceneTitle::Draw(void)
{
	m_pBG->Draw();
}