//==============================================================================
// File		SceneClear.h
// Comment	�N���A��ʃN���X
// Author	TOMOHIRO KOUNO
// Create	2014�N7��10��
//==============================================================================

//------------------------------------------------------------------------------
//	�C���N���[�h�K�[�h
//------------------------------------------------------------------------------
#ifndef _SCENECLEAR_H_
#define _SCENECLEAR_H_

//------------------------------------------------------------------------------
//	�C���N���[�h
//------------------------------------------------------------------------------
#include "SceneBase.h"

/**
* @brief �^�C�g����ʃN���X
*/
class CSceneClear :public CSceneBase
{
public:
	/**
	* @brief Constructor
	* @param	void
	* @return	void
	*/
	CSceneClear(void){}

	/**
	* @brief Destructor
	*/
	~CSceneClear(void){}

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
//End of File _SCENEClear_H_