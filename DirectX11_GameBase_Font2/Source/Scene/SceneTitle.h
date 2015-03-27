//==============================================================================
// File		SceneTitle.h
// Comment	タイトル画面クラス
// Author	TOMOHIRO KOUNO
// Create	2014年7月10日
//==============================================================================

//------------------------------------------------------------------------------
//	インクルードガード
//------------------------------------------------------------------------------
#ifndef _SCENETITLE_H_
#define _SCENETITLE_H_

//------------------------------------------------------------------------------
//	インクルード
//------------------------------------------------------------------------------
#include "SceneBase.h"

//------------------------------------------------------------------------------
//	前方宣言
//------------------------------------------------------------------------------
class CSprite;

/**
* @brief タイトル画面クラス
*/
class CSceneTitle :public CSceneBase
{
public:
	/**
	* @brief Constructor
	* @param	void
	* @return	void
	*/
	CSceneTitle(void);

	/**
	* @brief Destructor
	*/
	~CSceneTitle(void);

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
	CSprite* m_pBG;
	CSprite* m_pPushEnter;
	float m_alpha;
	float m_rate;
};
#endif
//End of File _SCENETITLE_H_