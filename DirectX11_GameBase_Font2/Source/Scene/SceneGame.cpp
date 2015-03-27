//==============================================================================
// File		SceneGame.cpp
// Comment	ゲーム画面クラス
// Author	TOMOHIRO KOUNO
// Create	2014年7月10日
//==============================================================================

//------------------------------------------------------------------------------
//	インクルード
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
//	人間の価値
//------------------------------------------------------------------------------
static const char* HUMAN_RANK[] =
{
	{"HAPPY CALL!!!"},
	{"(金のタマゴ)"},
	{ "汎用A" },
	{ "汎用B" },
	{ "汎用S" },
	{ "汎用D" },
	{ "汎用E" },
	{ "汎用F" },
	{ "汎用G" },
	{ "汎用H" },
	{ "汎用I" },
	{ "汎用J" }
};

//------------------------------------------------------------------------------
//	定数
//------------------------------------------------------------------------------
namespace ns_GameConstant
{
	static const int MAX_HUMAN = 30;

	static const float CURSOR_RADIUS = 5.0f;

	// 目標企業の当たり判定
	static const int DEST_POS_X = -100;
	static const int DEST_POS_Y = 150;
	static const int DEST_WIDTH = 700;
	static const int DEST_HEIGHT = 800;

	// スコア表示座標
	static const int SCORE_POS_X = 1000;
	static const int SCORE_POS_Y = 100;

	// 残り時間
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
	// 背景生成
	CSprite::PARAM param = { XMFLOAT2(0, 0), 0.0f, L"Resources/Texture/GAMEBG2.png" };
	m_pBG = new CSprite(param);
	m_pBG->SetWidth(ns_ConstantTable::SCREEN_WIDTH);
	m_pBG->SetHeight(ns_ConstantTable::SCREEN_HEIGHT);
	m_pBG->SetPolygonAlign(CSprite::ALIGN_LEFT_TOP);

	// 人間生成
	m_ppHuman = new CHuman*[MAX_HUMAN];
	for(int i = 0; i < MAX_HUMAN; i++)
	{
		m_ppHuman[i] = new CHuman();
	}

	// スコア用文字列
	m_pScoreString = new CFontString();

	// 残り時間設定
	m_nRestTime = REST_TIME;


	//ゲーム用のシードを設定
	Random::Reset((unsigned)time(NULL));
}

/**
* @brief Destructor
*/
CSceneGame::~CSceneGame(void)
{
	using namespace ns_GameConstant;
	//ゲームデータの破棄
	DestroyDatas();

	// 背景の開放
	SafeDelete(m_pBG);

	for(int i = 0; i < MAX_HUMAN; i++)
	{
		delete m_ppHuman[i];
	}

	SafeDeleteArray(m_ppHuman);

	SafeDelete(m_pScoreString);
}

/**
*	更新
*	@param	void
*	@return	void
*/
void CSceneGame::Update(void)
{
	UpdateExec();
}

/**
*	描画
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

	
	//Gameを終える時は必ずポーズモードをOFFにする
	//そうしないとポーズでないオブジェクトが更新されない。
	//フェードも更新されなくなる
	//CManager::GetObjectManager()->SetGamePause(false);
}

void CSceneGame::CreateObjectManager(void)
{
	//CObjectManager* pOM = nullptr;
//	pOM	= CManager::GetObjectManager();

	//フィールドやプレイや敵、球領域などを作成
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

	// マウス座標取得
	CInputMouse* pm = GETINPUTMOUSE;
	POINT* pos_mouse = pm->GetPosWorld();

	// オブジェクト更新
	for(int i = 0; i < MAX_HUMAN; i++)
	{
		m_ppHuman[i]->updateParentPos(pos_mouse->x, pos_mouse->y);
		m_ppHuman[i]->Update();
	}

	// 背景更新
	m_pBG->Update();

	// 当たり判定
	// マウス押してるとき
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
	// 離した瞬間
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

	// 企業と人間の当たり判定
	for(int i = 0; i < MAX_HUMAN; i++)
	{
		if(m_ppHuman[i]->IsStateReleased() && m_ppHuman[i]->IsHit(DEST_POS_X, DEST_POS_Y, DEST_WIDTH, DEST_HEIGHT))
		{
			// 得点加算
			m_nScorePoint += 500;
			// 人間のリセット
			m_ppHuman[i]->reset();
			// この人間の価値
		}
	}

	// スコアを文字に変換する処理
	UpdateScore();

	// 残り時間減少
	m_nRestTime--;
	if(m_nRestTime <= 0)
	{
		// リザルトへ
		CSceneManager* scene_manager = GETSCENEMANAGER;
		scene_manager->GotoScene(CSceneManager::SCENE_TYPE_RESULT);
	}
}
void CSceneGame::DrawExec(void)
{
	using namespace ns_GameConstant;
	// 背景描画
	m_pBG->Draw();

	// 建物とか

	// プレイヤーとか
	for(int i = 0; i < MAX_HUMAN; i++)
	{
		m_ppHuman[i]->Draw();
	}

	// スコア
	m_pScoreString->Draw();
}

/**
*	スコア更新処理
*	@param void
*	@return void
*/
void CSceneGame::UpdateScore()
{
	using namespace ns_GameConstant;

	// 7桁スコア
	const int DIGITS = 7;
	TCHAR aScore[DIGITS + 1];

	// 桁数ループ
	int nDecimalDivider = 1000000;
	// 次に表示したい点数
	int nNextPoint = m_nScorePoint;
	for(int nDig = 0; nDig < DIGITS; nDig++)
	{
		int nDispNum = nNextPoint / nDecimalDivider;
		nNextPoint %= nDecimalDivider;
		nDecimalDivider /= 10;

		// 数値を文字に変換
		aScore[nDig] = nDispNum + 0x30;	// アスキー文字分オフセット
	}
	// 終端文字
	aScore[DIGITS] = '\0';

	m_pScoreString->Update();
	m_pScoreString->printfString(XMFLOAT2(SCORE_POS_X, SCORE_POS_Y), aScore);

}
