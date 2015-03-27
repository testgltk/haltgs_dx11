//==============================================================================
// File		SceneResult.h
// Comment	���U���g��ʃN���X
// Author	TOMOHIRO KOUNO
// Create	2014�N7��10��
//==============================================================================

//------------------------------------------------------------------------------
//	�C���N���[�h�K�[�h
//------------------------------------------------------------------------------
#ifndef _SCENERESULT_H_
#define _SCENERESULT_H_

//------------------------------------------------------------------------------
//	�C���N���[�h
//------------------------------------------------------------------------------
#include "SceneBase.h"

//------------------------------------------------------------------------------
//	�O���錾
//------------------------------------------------------------------------------
class CSprite;
class CSpriteFlush;
class CSound;
class CFade;
class CScore;

/**
* @brief ���U���g��ʃN���X
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
	*	�X�V
	*	@param	void
	*	@return	void
	*/
	void Update(void);

	/**
	*	�`��
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
//End of File _SCENERESULT_H_