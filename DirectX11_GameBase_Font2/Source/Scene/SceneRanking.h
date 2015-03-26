//==============================================================================
// File		SceneRanking.h
// Comment	ランキング画面クラス
// Author	TOMOHIRO KOUNO
// Create	2014年7月10日
//==============================================================================

//------------------------------------------------------------------------------
//	インクルードガード
//------------------------------------------------------------------------------
#ifndef _SCENERANKING_H_
#define _SCENERANKING_H_

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
class CScore;
class CFade;
class CTimer;

/**
* @brief ランキング画面クラス
*/
class CSceneRanking :public CSceneBase
{
public:
	/**
	* @brief Constructor
	* @param	void
	* @return	void
	*/
	CSceneRanking(void);

	/**
	* @brief Destructor
	*/
	~CSceneRanking(void);

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
	CSound*			m_pBGM;			///> BGM1個数
	CSound*			m_pSEDecision;	///> 決定キー
	CFade*			m_pFade;		///> フェード
	CFade*			m_pFadeBackUVBG;///> 通常フェード用の下地
	CSprite*		m_BG;			///> 背景
	CSprite*		m_pLogo;		///> ロゴ
	CSpriteFlush*	m_pAnyKey;		///> 案内用
	CSprite*		m_pScoreText;	///> スコアのテキスト
	CScore*			m_pScore;		///> スコア表示用
	CTimer*			m_pToTitleTimer;///> タイトル遷移用タイマー
};
#endif
//End of File _SCENERANKING_H_