//==============================================================================
// File		SceneDebug.h
// Comment	�f�o�b�O�p��ʃN���X
// Author	TOMOHIRO KOUNO
// Create	2014�N7��10��
//==============================================================================

//------------------------------------------------------------------------------
//	�C���N���[�h�K�[�h
//------------------------------------------------------------------------------
#ifndef _SCENEDEBUG_H_
#define _SCENEDEBUG_H_

//------------------------------------------------------------------------------
//	�C���N���[�h
//------------------------------------------------------------------------------
#include "SceneBase.h"

//------------------------------------------------------------------------------
//	�O���Q��
//------------------------------------------------------------------------------
class CGameObject;

/**
* @brief �^�C�g����ʃN���X
*/
class CSceneDebug :public CSceneBase
{
public:
	/**
	* @brief Constructor
	* @param	void
	* @return	void
	*/
	CSceneDebug(void);

	/**
	* @brief Destructor
	*/
	~CSceneDebug(void);

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
//End of File _SCENEDebug_H_