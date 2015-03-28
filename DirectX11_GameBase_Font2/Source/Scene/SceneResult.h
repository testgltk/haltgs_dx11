//==============================================================================
// File		SceneResult.h
// Comment	リザルト画面クラス
// Author	TOMOHIRO KOUNO
// Create	2014年7月10日
//==============================================================================

//------------------------------------------------------------------------------
//	インクルードガード
//------------------------------------------------------------------------------
#ifndef _SCENERESULT_H_
#define _SCENERESULT_H_

//------------------------------------------------------------------------------
//	インクルード
//------------------------------------------------------------------------------
#include "SceneBase.h"

//------------------------------------------------------------------------------
//	前方宣言
//------------------------------------------------------------------------------
class CSprite;
class CSpriteFlush;
class CSound;
class CFade;
class CScore;

/**
* @brief リザルト画面クラス
*/
class CSceneResult :public CSceneBase
{
public:

	/**
	* @brief Constructor
	* @param	void
	* @return	void
	*/
	CSceneResult(void);

	/**
	* @brief Destructor
	*/
	~CSceneResult(void);

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

	int m_nScorePoint;
};
#endif
//End of File _SCENERESULT_H_