//==============================================================================
// File		SceneGameOver.h
// Comment	���U���g��ʃN���X
// Author	TOMOHIRO KOUNO
// Create	2014�N7��10��
//==============================================================================

//------------------------------------------------------------------------------
//	�C���N���[�h�K�[�h
//------------------------------------------------------------------------------
#ifndef _SCENEGAMEOVER_H_
#define _SCENEGAMEOVER_H_

//------------------------------------------------------------------------------
//	�C���N���[�h
//------------------------------------------------------------------------------
#include "SceneBase.h"

//------------------------------------------------------------------------------
//	�O���錾
//------------------------------------------------------------------------------

/**
* @brief ���U���g��ʃN���X
*/
class CSceneGameOver :public CSceneBase
{
public:

	/**
	* @brief Constructor
	* @param	void
	* @return	void
	*/
	CSceneGameOver(void);

	/**
	* @brief Destructor
	*/
	~CSceneGameOver(void);

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

};
#endif
//End of File _SCENEGameOver_H_