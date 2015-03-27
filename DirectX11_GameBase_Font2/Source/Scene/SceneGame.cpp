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

// system
#include "system/SystemManager.h"

// sprite
#include "Sprite/Sprite.h"

// human
#include "human/human.h"

// input
#include "input/inputmouse.h"

// Fonttexture
#include "fonttexture/FontString.h"

//------------------------------------------------------------------------------
//	�l�Ԃ̉��l
//------------------------------------------------------------------------------
static const char* HUMAN_RANK[] =
{
	{"HAPPY CALL!!!"},
	{"(���̃^�}�S)"},
	{ "�ėpA" },
	{ "�ėpB" },
	{ "�ėpS" },
	{ "�ėpD" },
	{ "�ėpE" },
	{ "�ėpF" },
	{ "�ėpG" },
	{ "�ėpH" },
	{ "�ėpI" },
	{ "�ėpJ" }
};

//------------------------------------------------------------------------------
//	�萔
//------------------------------------------------------------------------------
namespace ns_GameConstant
{
	static const int MAX_HUMAN = 30;

	static const float CURSOR_RADIUS = 5.0f;

	// �ڕW��Ƃ̓����蔻��
	static const int DEST_POS_X = -100;
	static const int DEST_POS_Y = 150;
	static const int DEST_WIDTH = 700;
	static const int DEST_HEIGHT = 800;

	// �X�R�A�\�����W
	static const int SCORE_POS_X = 1000;
	static const int SCORE_POS_Y = 100;

	// �c�莞��
	static const int REST_TIME = 600;
};

/**
* @brief Constructor
* @param	void
* @return	void
*/
CSceneGame::CSceneGame(void) :
m_nScorePoint(0)
{
	using namespace ns_GameConstant;
	// �w�i����
	CSprite::PARAM param = { XMFLOAT2(0, 0), 0.0f, L"Resources/Texture/GAMEBG2.png" };
	m_pBG = new CSprite(param);
	m_pBG->SetWidth(ns_ConstantTable::SCREEN_WIDTH);
	m_pBG->SetHeight(ns_ConstantTable::SCREEN_HEIGHT);
	m_pBG->SetPolygonAlign(CSprite::ALIGN_LEFT_TOP);

	// �l�Ԑ���
	m_ppHuman = new CHuman*[MAX_HUMAN];
	for(int i = 0; i < MAX_HUMAN; i++)
	{
		m_ppHuman[i] = new CHuman();
	}

	// �X�R�A�p������
	m_pScoreString = new CFontString();

	// �c�莞�Ԑݒ�
	m_nRestTime = REST_TIME;


	//�Q�[���p�̃V�[�h��ݒ�
	Random::Reset((unsigned)time(NULL));
}

/**
* @brief Destructor
*/
CSceneGame::~CSceneGame(void)
{
	using namespace ns_GameConstant;
	//�Q�[���f�[�^�̔j��
	DestroyDatas();

	// �w�i�̊J��
	SafeDelete(m_pBG);

	for(int i = 0; i < MAX_HUMAN; i++)
	{
		delete m_ppHuman[i];
	}

	SafeDeleteArray(m_ppHuman);

	SafeDelete(m_pScoreString);
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
	using namespace ns_GameConstant;

	// �}�E�X���W�擾
	CInputMouse* pm = GETINPUTMOUSE;
	POINT* pos_mouse = pm->GetPosWorld();

	// �I�u�W�F�N�g�X�V
	for(int i = 0; i < MAX_HUMAN; i++)
	{
		m_ppHuman[i]->updateParentPos(pos_mouse->x, pos_mouse->y);
		m_ppHuman[i]->Update();
	}

	// �w�i�X�V
	m_pBG->Update();

	// �����蔻��
	// �}�E�X�����Ă�Ƃ�
	if(pm->IsLeftTrigger())
	{
		for(int i = 0; i < MAX_HUMAN; i++)
		{
			if(m_ppHuman[i]->IsHit(pos_mouse->x, pos_mouse->y, CURSOR_RADIUS))
			{
				m_ppHuman[i]->setSelected(true);
				m_ppHuman[i]->setState(CHuman::SELECTED);
				m_ppHuman[i]->setParentPos(pos_mouse->x, pos_mouse->y);
			}
		}	
	}
	// �������u��
	if(pm->IsLeftRelease())
	{
		for(int i = 0; i < MAX_HUMAN; i++)
		{
			if(m_ppHuman[i]->onRelease())
			{
				m_ppHuman[i]->setSelected(false);
				m_ppHuman[i]->setState(CHuman::RELEASED);
			}
		}
	}

	// ��ƂƐl�Ԃ̓����蔻��
	for(int i = 0; i < MAX_HUMAN; i++)
	{
		if(m_ppHuman[i]->IsStateReleased() && m_ppHuman[i]->IsHit(DEST_POS_X, DEST_POS_Y, DEST_WIDTH, DEST_HEIGHT))
		{
			// ���_���Z
			m_nScorePoint += 500;
			// �l�Ԃ̃��Z�b�g
			m_ppHuman[i]->reset();
			// ���̐l�Ԃ̉��l
		}
	}

	// �X�R�A�𕶎��ɕϊ����鏈��
	UpdateScore();

	// �c�莞�Ԍ���
	m_nRestTime--;
	if(m_nRestTime <= 0)
	{
		// ���U���g��
		CSceneManager* scene_manager = GETSCENEMANAGER;
		scene_manager->GotoScene(CSceneManager::SCENE_TYPE_RESULT);
	}
}
void CSceneGame::DrawExec(void)
{
	using namespace ns_GameConstant;
	// �w�i�`��
	m_pBG->Draw();

	// �����Ƃ�

	// �v���C���[�Ƃ�
	for(int i = 0; i < MAX_HUMAN; i++)
	{
		m_ppHuman[i]->Draw();
	}

	// �X�R�A
	m_pScoreString->Draw();
}

/**
*	�X�R�A�X�V����
*	@param void
*	@return void
*/
void CSceneGame::UpdateScore()
{
	using namespace ns_GameConstant;

	// 7���X�R�A
	const int DIGITS = 7;
	TCHAR aScore[DIGITS + 1];

	// �������[�v
	int nDecimalDivider = 1000000;
	// ���ɕ\���������_��
	int nNextPoint = m_nScorePoint;
	for(int nDig = 0; nDig < DIGITS; nDig++)
	{
		int nDispNum = nNextPoint / nDecimalDivider;
		nNextPoint %= nDecimalDivider;
		nDecimalDivider /= 10;

		// ���l�𕶎��ɕϊ�
		aScore[nDig] = nDispNum + 0x30;	// �A�X�L�[�������I�t�Z�b�g
	}
	// �I�[����
	aScore[DIGITS] = '\0';

	m_pScoreString->Update();
	m_pScoreString->printfString(XMFLOAT2(SCORE_POS_X, SCORE_POS_Y), aScore);

}
