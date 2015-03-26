//==============================================================================
// File		SceneDemo.cpp
// Comment	���S��ʃN���X
// Author	TOMOHIRO KOUNO
// Create	2014�N7��10��
//==============================================================================

//------------------------------------------------------------------------------
//	�C���N���[�h
//------------------------------------------------------------------------------
#include "SceneDemo.h"

//------------------------------------------------------------------------------
//	�萔
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

	
	//�f���J�n
#if 1
	//CManager::GetXInput()->SetKeyStateMode(CInputXInput::KEYSTATE_MODE_LOAD);
	//CManager::GetKeyboard()->StartLoadKeyState();
#else
	//�^��J�n
	CManager::GetKeyboard()->StartSaveKeyState();

#endif
}

/**
* @brief Destructor
*/
CSceneDemo::~CSceneDemo(void)
{
	

	//�f���I��
#if 1
	//CInputKeyboard* pKeyboard = CManager::GetKeyboard();
	//CManager::GetXInput()->SetKeyStateMode(CInputXInput::KEYSTATE_MODE_NONE);
	//pKeyboard->EndLoadKeyState();
#else
	//�^��I��
	//CManager::GetKeyboard()->EndSaveKeyState();
#endif
}

/**
*	�X�V
*	@param	void
*	@return	void
*/
void CSceneDemo::Update(void)
{
	
	//�X�V
	UpdateExec();

}

/**
*	�`��
*	@param	void
*	@return	void
*/
void CSceneDemo::Draw(void)
{
	//�`��
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