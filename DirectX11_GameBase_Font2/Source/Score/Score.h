//==============================================================================
// File		Score.h
// Comment	スコアクラス
// Author	Ryo Kobayashi
// Create	2015年3月27日
//==============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

/**
* @brief スコアクラス
*/
class CScore
{
public:
	/**
	* @brief Constructor
	* @param	void
	* @return	void
	*/
	CScore(void);

	/**
	* @brief Destructor
	*/
	virtual ~CScore(void);

	/**
	*	Update Pure Fuction
	*	@param	void
	*	@return	void
	*/
	virtual void Update(void);

	/**
	*	Draw Pure Fuction
	*	@param	void
	*	@return	void
	*/
	virtual void Draw(void);

	/**
	*	スコア設定
	*/
	void SetScore(int nScore);

private:

	int m_nScore;	//! スコア
};

#endif	// _SCORE_H_

// EOF