//==============================================================================
// File		SceneGame.h
// Comment	タイトル画面クラス
// Author	TOMOHIRO KOUNO
// Create	2014年7月10日
//==============================================================================

//------------------------------------------------------------------------------
//	インクルードガード
//------------------------------------------------------------------------------
#ifndef _SCENEGAME_H_
#define _SCENEGAME_H_

//------------------------------------------------------------------------------
//	インクルード
//------------------------------------------------------------------------------
#include "SceneBase.h"

//------------------------------------------------------------------------------
//	前方宣言
//------------------------------------------------------------------------------
class CSprite;
class CHuman;
class CFontString;

/**
* @brief タイトル画面クラス
*/
class CSceneGame :public CSceneBase
{
public:

	/**
	* @brief Constructor
	* @param	void
	* @return	void
	*/
	CSceneGame(void);

	/**
	* @brief Destructor
	*/
	virtual ~CSceneGame(void);

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
	* @brief	動的データの作成
	* @param	void
	* @return	void
	*/
	void CreateDatas(void);

	/**
	* @brief	動的データの作成(オブジェクト管理クラス用)
	* @param	void
	* @return	void
	*/
	void CreateObjectManager(void);

	/**
	* @brief	動的データの破棄
	* @param	void
	* @return	void
	*/
	void DestroyDatas(void);

	/**
	* @brief	動的データの破棄(オブジェクト管理クラス用)
	* @param	void
	* @return	void
	*/
	void DestroyObjectManager(void);

	//以下本当の更新実行 リーク問題のチェックのためにさらにスコープを用意する

	/**
	*	実際の更新(メモリリーク調査時に除けるように関数をもうけてます)
	*	@param	void
	*	@return	void
	*/
	void UpdateExec(void);

	/**
	*	実際の描画(メモリリーク調査時に除けるように関数をもうけてます)
	*	@param	void
	*	@return	void
	*/
	void DrawExec(void);

	/**
	*	スコア更新処理
	*	@param void
	*	@return void
	*/
	void UpdateScore();

private:
	
	CSprite* m_pBG;	//! 背景
	CHuman** m_ppHuman; //! 人間

	int m_nScorePoint;
	CFontString* m_pScoreString; //! スコア表示用文字列

	int m_nRestTime;
};
#endif
//End of File _SCENEGame_H_