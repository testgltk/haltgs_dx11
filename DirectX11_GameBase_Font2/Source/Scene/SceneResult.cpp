//==============================================================================
// File		SceneResult.cpp
// Comment	���U���g��ʃN���X
// Author	TOMOHIRO KOUNO
// Create	2014�N7��10��
//==============================================================================

//------------------------------------------------------------------------------
//	�C���N���[�h
//------------------------------------------------------------------------------
#include "SceneResult.h"
#include "system/systemmanager.h"
#include "Sprite/Sprite.h"

//------------------------------------------------------------------------------
//	�萔
//------------------------------------------------------------------------------
namespace ns_ResultConstant
{
	
};

/**
* @brief Constructor
* @param	void
* @return	void
*/
CSceneResult::CSceneResult(void)
{
	//���O��Ԃ̎g�p
	using namespace ns_ResultConstant;

	CSprite::PARAM bg_param = { XMFLOAT2(0, 0), 0.0f, L"Resources/Texture/BlockTexture.png" };
	CSprite::PARAM pe_param = { XMFLOAT2(ns_ConstantTable::SCREEN_WIDTH * 0.5f, ns_ConstantTable::SCREEN_HEIGHT - 100.0f), 0.0f, L"Resources/Texture/PUSHENTER.png" };

	m_pBG = new CSprite(bg_param);
	m_pBG->SetWidth(ns_ConstantTable::SCREEN_WIDTH);
	m_pBG->SetHeight(ns_ConstantTable::SCREEN_HEIGHT);
	m_pBG->SetPolygonAlign(CSprite::ALIGN_LEFT_TOP);

	m_pPushEnter = new CSprite(pe_param);
	m_alpha = 0.0f;
	m_rate = 0.1f;
}

/**
* @brief Destructor
*/
CSceneResult::~CSceneResult(void)
{
	SafeDelete(m_pBG);
	SafeDelete(m_pPushEnter);
}

/**
*	�X�V
*	@param	void
*	@return	void
*/
void CSceneResult::Update(void)
{
	//���O��Ԃ̎g�p
	using namespace ns_ResultConstant;

	m_pBG->Update();

	m_alpha += m_rate;

	if(m_alpha <= 0.0f)
	{
		m_alpha = 0.0f;
		m_rate *= -1;
	}
	if(m_alpha >= 1.0f)
	{
		m_alpha = 1.0f;
		m_rate *= -1;
	}

	m_pPushEnter->SetColor(XMFLOAT4(1.0f, 1.0f, 1.0f, m_alpha));

	m_pPushEnter->Update();

	CInputKeyboard* input_keyboard = GETINPUTKEYBOARD;

	if(input_keyboard->IsKeyTrigger(DIK_RETURN))
	{
		CSceneManager* scene_manager = GETSCENEMANAGER;
		scene_manager->GotoScene(CSceneManager::SCENE_TYPE_TITLE);
	}
}

/**
*	�`��
*	@param	void
*	@return	void
*/
void CSceneResult::Draw(void)
{
	m_pBG->Draw();
	m_pPushEnter->Draw();
}