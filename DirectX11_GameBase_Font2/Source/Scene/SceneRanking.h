//==============================================================================
// File		SceneRanking.h
// Comment	�����L���O��ʃN���X
// Author	TOMOHIRO KOUNO
// Create	2014�N7��10��
//==============================================================================

//------------------------------------------------------------------------------
//	�C���N���[�h�K�[�h
//------------------------------------------------------------------------------
#ifndef _SCENERANKING_H_
#define _SCENERANKING_H_

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
class CScore;
class CFade;
class CTimer;

/**
* @brief �����L���O��ʃN���X
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
	CSound*			m_pBGM;			///> BGM1��
	CSound*			m_pSEDecision;	///> ����L�[
	CFade*			m_pFade;		///> �t�F�[�h
	CFade*			m_pFadeBackUVBG;///> �ʏ�t�F�[�h�p�̉��n
	CSprite*		m_BG;			///> �w�i
	CSprite*		m_pLogo;		///> ���S
	CSpriteFlush*	m_pAnyKey;		///> �ē��p
	CSprite*		m_pScoreText;	///> �X�R�A�̃e�L�X�g
	CScore*			m_pScore;		///> �X�R�A�\���p
	CTimer*			m_pToTitleTimer;///> �^�C�g���J�ڗp�^�C�}�[
};
#endif
//End of File _SCENERANKING_H_