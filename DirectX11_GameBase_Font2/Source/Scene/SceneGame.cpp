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
	
}
void CSceneGame::DrawExec(void)
{


}