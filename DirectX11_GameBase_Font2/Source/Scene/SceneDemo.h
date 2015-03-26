//==============================================================================
// File		SceneDemo.h
// Comment	デモ画面クラス
// Author	TOMOHIRO KOUNO
// Create	2014年7月10日
//==============================================================================

//------------------------------------------------------------------------------
//	インクルードガード
//------------------------------------------------------------------------------
#ifndef _SCENEDEMO_H_
#define _SCENEDEMO_H_

//------------------------------------------------------------------------------
//	インクルード
//------------------------------------------------------------------------------
#include "SceneBase.h"

//------------------------------------------------------------------------------
//	前方宣言
//------------------------------------------------------------------------------

/**
* @brief ロゴ画面クラス
*/
class CSceneDemo :public CSceneBase
{
public:
	/**
	* @brief Constructor
	* @param	void
	* @return	void
	*/
	CSceneDemo(void);

	/**
	* @brief Destructor
	*/
	~CSceneDemo(void);

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
	*	実際の更新
	*	@param	void
	*	@return	void
	*/
	void UpdateExec(void);

	/**
	*	実際の描画
	*	@param	void
	*	@return	void
	*/
	void DrawExec(void);

private:

};
#endif
//End of File _SCENEDEMO_H_