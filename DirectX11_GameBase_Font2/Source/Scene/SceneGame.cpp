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
#include "Sprite/Sprite.h"


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
	// �w�i����
	CSprite::PARAM param = { XMFLOAT2(0, 0), 0.0f, L"Resources/Texture/field001.jpg" };
	m_pBG = new CSprite(param);
	m_pBG->SetWidth(ns_ConstantTable::SCREEN_WIDTH);
	m_pBG->SetHeight(ns_ConstantTable::SCREEN_HEIGHT);
	m_pBG->SetPolygonAlign(CSprite::ALIGN_LEFT_TOP);

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

	// �w�i�̊J��
	SafeDelete(m_pBG);
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
	// �I�u�W�F�N�g�X�V

	// �w�i�X�V
	m_pBG->Update();

	// �����蔻��
}
void CSceneGame::DrawExec(void)
{
	// �w�i�`��
	m_pBG->Draw();

	// �����Ƃ�

	// �v���C���[�Ƃ�
}