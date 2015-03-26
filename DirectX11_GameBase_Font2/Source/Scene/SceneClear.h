//==============================================================================
// File		SceneClear.h
// Comment	クリア画面クラス
// Author	TOMOHIRO KOUNO
// Create	2014年7月10日
//==============================================================================

//------------------------------------------------------------------------------
//	インクルードガード
//------------------------------------------------------------------------------
#ifndef _SCENECLEAR_H_
#define _SCENECLEAR_H_

//------------------------------------------------------------------------------
//	インクルード
//------------------------------------------------------------------------------
#include "SceneBase.h"

/**
* @brief タイトル画面クラス
*/
class CSceneClear :public CSceneBase
{
public:
	/**
	* @brief Constructor
	* @param	void
	* @return	void
	*/
	CSceneClear(void){}

	/**
	* @brief Destructor
	*/
	~CSceneClear(void){}

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

private:
};
#endif
//End of File _SCENEClear_H_