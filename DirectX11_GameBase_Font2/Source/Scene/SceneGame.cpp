//==============================================================================
// File		SceneGame.cpp
// Comment	�Q�[����ʃN���X
// Author	TOMOHIRO KOUNO
// Create	2014�N7��10��
//==============================================================================

//------------------------------------------------------------------------------
//	�C���N���[�h
//------------------------------------------------------------------------------
#include "SceneGame.h"



//------------------------------------------------------------------------------
//	�萔
//------------------------------------------------------------------------------
namespace ns_GameConstant
{
	
};

/**
* @brief Constructor
* @param	void
* @return	void
*/
CSceneGame::CSceneGame(void)
{
	//�J�����ݒ�����Z�b�g


	//�Q�[���X�R�A�N���A

	//�Q�[���f�[�^�̓��I����


	//�Q�[���p�̃V�[�h��ݒ�
	Random::Reset((unsigned)time(NULL));
}

/**
* @brief Destructor
*/
CSceneGame::~CSceneGame(void)
{
	//�Q�[���f�[�^�̔j��
	DestroyDatas();
}

/**
*	�X�V
*	@param	void
*	@return	void
*/
void CSceneGame::Update(void)
{
	UpdateExec();
}

/**
*	�`��
*	@param	void
*	@return	void
*/
void CSceneGame::Draw(void)
{
	DrawExec();
}

void CSceneGame::CreateDatas(void)
{
	using namespace ns_GameConstant;

	
}

void CSceneGame::DestroyDatas(void)
{
	DestroyObjectManager();

	
	//Game���I���鎞�͕K���|�[�Y���[�h��OFF�ɂ���
	//�������Ȃ��ƃ|�[�Y�łȂ��I�u�W�F�N�g���X�V����Ȃ��B
	//�t�F�[�h���X�V����Ȃ��Ȃ�
	//CManager::GetObjectManager()->SetGamePause(false);
}

void CSceneGame::CreateObjectManager(void)
{
	//CObjectManager* pOM = nullptr;
//	pOM	= CManager::GetObjectManager();

	//�t�B�[���h��v���C��G�A���̈�Ȃǂ��쐬
	//pOM->CreateSkyBox();
	//pOM->CreateMeshField();
	//pOM->CreateMeshWalls();
	//pOM->CreateColliders();
	//pOM->CreateEnemys();
	//pOM->CreateScore();
	//pOM->CreateHitScore();
	//pOM->CreateHitTimer();
	//pOM->CreateTimer();
	//pOM->CreatePlayer();
	//pOM->CreateHPGage();
	//pOM->CreateSPGage();
	//pOM->CreateBullets();
	//pOM->CreateItems();
	//pOM->CreateBossEnemy();
	//pOM->CreateEnemyWave();
	//pOM->CreateEnemyWithWaveData(0);
	//pOM->CreateIcePillars();
	//pOM->CreateIceRocks();
}

void CSceneGame::DestroyObjectManager(void)
{
	
}

void CSceneGame::UpdateExec(void)
{
	
}
void CSceneGame::DrawExec(void)
{


}