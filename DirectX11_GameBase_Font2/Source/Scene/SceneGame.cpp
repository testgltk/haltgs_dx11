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
static const TCHAR* HUMAN_RANK[] =
{
	{L"HAPPY CALL!!!"},
	{L"(���̃^�}�S)"},
	{L"�ėpA" },
	{L"�ėpB" },
	{L"�ėpS" },
	{L"�ėpD" },
	{L"�ėpE" },
	{L"�ėpF" },
	{L"�ėpG" },
	{L"�ėpH" },
	{L"�ėpI" },
	{L"�ėpJ" }
};
static const int MAX_HUMAN_RANK = sizeof(HUMAN_RANK) / sizeof(HUMAN_RANK[0]);

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

// �}�N��
#define STRING_USE

/**
* @brief Constructor
* @param	void
* @return	void
*/
CSceneGame::CSceneGame(void) :
m_nScorePoint(0),
m_aRankBuff(),
m_nTempPtr(0),
m_aRankPos(),
m_aColor(),
m_nColorPtr(0)
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

	// �c�莞�Ԑݒ�
	m_nRestTime = REST_TIME;

	// �����N�o�b�t�@������
	for(int i = 0; i < MAX_RANK; i++)
	{
		m_aRankBuff[i] = -1;
	}

	// �J���[�o�b�t�@������
	float ftemp = 0;
	for(int i = 0; i < MAX_COLOR; i++)
	{
		ftemp = (MAX_COLOR - i) / (float)MAX_COLOR;
		m_aColor[i] = XMFLOAT4(ftemp, 0, 0, 1);
	}


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

	CFontString* pString = GETFONT;
	// ��ƂƐl�Ԃ̓����蔻��
	for(int i = 0; i < MAX_HUMAN; i++)
	{
		if(m_ppHuman[i]->IsStateReleased() && m_ppHuman[i]->IsHit(DEST_POS_X, DEST_POS_Y, DEST_WIDTH, DEST_HEIGHT))
		{
			// ���_���Z
			m_nScorePoint += 500;
			// ���̐l�Ԃ̉��l��\�����邽�߂̐ݒ�
			m_aRankPos[m_nTempPtr] = m_ppHuman[i]->getPos();
			m_aRankBuff[m_nTempPtr] = Random::GetRange(0, MAX_HUMAN_RANK - 1);
			m_nTempPtr++; m_nTempPtr %= MAX_RANK;
			// �l�Ԃ̃��Z�b�g
			m_ppHuman[i]->reset();
		}
	}


	// �X�R�A�𕶎��ɕϊ����鏈��
	UpdateScore();
	// ���Ԃ𕶎���ϊ�
	UpdateTime();

	// �l�Ԃ̉��l�\��
	for(int i = 0; i < MAX_RANK; i++)
	{
		if(-1 != m_aRankBuff[i])
		{
			pString->SetColor(m_aColor[m_nColorPtr]);
			pString->printfString(m_aRankPos[i], HUMAN_RANK[m_aRankBuff[i]]);
		}
	}
	// �J���[�A�j���[�V�����ݒ�
	m_nColorPtr++; m_nColorPtr %= MAX_COLOR;

	// �c�莞�Ԍ���
	m_nRestTime--;
	if(m_nRestTime <= 0)
	{
		// �X�R�A�ݒ�
		CSystemManager::GetInstance()->setScore(m_nScorePoint);
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
	TCHAR aScore[DIGITS + 1] = L"";

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

	CFontString *pStr = GETFONT;
	pStr->printfString(XMFLOAT2(SCORE_POS_X, SCORE_POS_Y), aScore);
}

/**
*	���ԍX�V����
*	@param void
*	@return void
*/
void CSceneGame::UpdateTime()
{
	using namespace ns_GameConstant;

	// 7���X�R�A
	const int DIGITS = 2;
	TCHAR aScore[DIGITS + 1] = L"";

	// �b����
	int nSec = (int)(m_nRestTime / 60.0f);
	// �������[�v
	int nDecimalDivider = 10;
	// ���ɕ\���������_��
	int nNextPoint = nSec;
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

	CFontString *pStr = GETFONT;
	pStr->printfString(XMFLOAT2(200, SCORE_POS_Y), aScore);
}
