//==============================================================================
// File		SceneManager.h
// Comment	シーン管理クラス
// Author	TOMOHIRO KOUNO
// Create	2014年7月11日
//==============================================================================

//------------------------------------------------------------------------------
//	インクルードガード
//------------------------------------------------------------------------------
#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

//------------------------------------------------------------------------------
//	インクルード
//------------------------------------------------------------------------------
#include "SceneLogo.h"
#include "SceneTitle.h"
#include "SceneDemo.h"
#include "SceneGame.h"
#include "SceneResult.h"
#include "SceneRanking.h"
#include "SceneGameOver.h"

//------------------------------------------------------------------------------
//	前方参照
//------------------------------------------------------------------------------
class CSceneBase;
/**
* @brief シーン管理クラス
*/
class CSceneManager :public ISystem
{
public:

	enum SCENE_TYPE
	{
		SCENE_TYPE_LOGO,
		SCENE_TYPE_TITLE,
		SCENE_TYPE_DEMO,
		SCENE_TYPE_GAME,
		SCENE_TYPE_RESULT,
		SCENE_TYPE_RANKING,
		SCENE_TYPE_GAMEOVER,
	};

	/**
	* @brief Constructor
	* @param	void
	* @return	void
	*/
	CSceneManager(void);

	/**
	* @brief Destructor
	*/
	~CSceneManager(void);

	/**
	*	終了
	*	@param	void
	*	@return	void
	*/
	void Finalize(void);

	/**
	*	更新
	*	@param	void
	*	@return	void
	*/
	void Update(void);

	/**
	*	描画
	*	@param	void
	*	@return	void
	*/
	void Draw(void);

	/**
	*	遷移処理実行
	*	@param	void
	*	@return	void
	*/
	void Change(void);

	/**
	*	同一シーンを再読み込みする
	*	@param	void
	*	@return	void
	*/
	void ReloadScene(void);

	/**
	*	シーンの遷移
	*	@param	Type	遷移したいシーンへのタイプ
	*	@return	void
	*/
	void GotoScene(SCENE_TYPE Type);

	/**
	*	現在管理シーンの返却
	*	@param	void
	*	@return	m_pScene		現在のシーン情報
	*/
	CSceneBase* GetCurrentScene(void);

	/**
	*	現在管理シーンタイプの返却
	*	@param	void
	*	@return	m_pScene		現在のシーンタイプ情報
	*/
	SCENE_TYPE GetCurrentSceneType(void);

private:
	CSceneBase *m_pScene;		///>	現在のシーン
	CSceneBase *m_pSceneNext;	///>	次回のシーン
	SCENE_TYPE  m_SceneType;	///>	現在シーンのタイプ
	SCENE_TYPE  m_SceneTypeNext;///>	次回のシーンタイプ
	bool	    m_bReloadScene;	///>	同じシーンを繰り返し読み込むフラグ
};
#endif
//End of File _SCENEMANAGER_H_