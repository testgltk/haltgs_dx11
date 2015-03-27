//==============================================================================
// File		Score.h
// Comment	�X�R�A�N���X
// Author	Ryo Kobayashi
// Create	2015�N3��27��
//==============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

/**
* @brief �X�R�A�N���X
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
	*	�X�R�A�ݒ�
	*/
	void SetScore(int nScore);

private:

	int m_nScore;	//! �X�R�A
};

#endif	// _SCORE_H_

// EOF