//==============================================================================
// File		SceneLogo.cpp
// Comment	���S��ʃN���X
// Author	TOMOHIRO KOUNO
// Create	2014�N7��10��
//==============================================================================

//------------------------------------------------------------------------------
//	�C���N���[�h
//------------------------------------------------------------------------------
#include "SceneLogo.h"
#include "System/SystemManager.h"

//------------------------------------------------------------------------------
//	�萔
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
*	�X�V
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
*	�`��
*	@param	void
*	@return	void
*/
void CSceneLogo::Draw(void)
{

}