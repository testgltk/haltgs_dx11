//==============================================================================
// File		SceneTitle.h
// Comment	�^�C�g����ʃN���X
// Author	TOMOHIRO KOUNO
// Create	2014�N7��10��
//==============================================================================

//------------------------------------------------------------------------------
//	�C���N���[�h�K�[�h
//------------------------------------------------------------------------------
#ifndef _SCENETITLE_H_
#define _SCENETITLE_H_

//------------------------------------------------------------------------------
//	�C���N���[�h
//------------------------------------------------------------------------------
#include "SceneBase.h"

//------------------------------------------------------------------------------
//	�O���錾
//------------------------------------------------------------------------------
class CSprite;

/**
* @brief �^�C�g����ʃN���X
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
};
#endif
//End of File _SCENETITLE_H_