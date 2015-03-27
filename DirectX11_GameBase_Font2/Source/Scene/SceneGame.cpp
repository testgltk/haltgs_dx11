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
#include "Sprite/Sprite.h"


//------------------------------------------------------------------------------
//	定数
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
	// 背景生成
	CSprite::PARAM param = { XMFLOAT2(0, 0), 0.0f, L"Resources/Texture/field001.jpg" };
	m_pBG = new CSprite(param);
	m_pBG->SetWidth(ns_ConstantTable::SCREEN_WIDTH);
	m_pBG->SetHeight(ns_ConstantTable::SCREEN_HEIGHT);
	m_pBG->SetPolygonAlign(CSprite::ALIGN_LEFT_TOP);

	//カメラ設定をリセット


	//ゲームスコアクリア

	//ゲームデータの動的生成


	//ゲーム用のシードを設定
	Random::Reset((unsigned)time(NULL));
}

/**
* @brief Destructor
*/
CSceneGame::~CSceneGame(void)
{
	//ゲームデータの破棄
	DestroyDatas();

	// 背景の開放
	SafeDelete(m_pBG);
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
	// オブジェクト更新

	// 背景更新
	m_pBG->Update();

	// 当たり判定
}
void CSceneGame::DrawExec(void)
{
	// 背景描画
	m_pBG->Draw();

	// 建物とか

	// プレイヤーとか
}