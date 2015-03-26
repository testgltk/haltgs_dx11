//==============================================================================
// File		SceneDemo.h
// Comment	�f����ʃN���X
// Author	TOMOHIRO KOUNO
// Create	2014�N7��10��
//==============================================================================

//------------------------------------------------------------------------------
//	�C���N���[�h�K�[�h
//------------------------------------------------------------------------------
#ifndef _SCENEDEMO_H_
#define _SCENEDEMO_H_

//------------------------------------------------------------------------------
//	�C���N���[�h
//------------------------------------------------------------------------------
#include "SceneBase.h"

//------------------------------------------------------------------------------
//	�O���錾
//------------------------------------------------------------------------------

/**
* @brief ���S��ʃN���X
*/
class CSceneDemo :public CSceneBase
{
public:
	/**
	* @brief Constructor
	* @param	void
	* @return	void
	*/
	CSceneDemo(void);

	/**
	* @brief Destructor
	*/
	~CSceneDemo(void);

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

	/**
	* @brief	���I�f�[�^�̍쐬
	* @param	void
	* @return	void
	*/
	void CreateDatas(void);

	/**
	* @brief	���I�f�[�^�̍쐬(�I�u�W�F�N�g�Ǘ��N���X�p)
	* @param	void
	* @return	void
	*/
	void CreateObjectManager(void);

	/**
	* @brief	���I�f�[�^�̔j��
	* @param	void
	* @return	void
	*/
	void DestroyDatas(void);

	/**
	* @brief	���I�f�[�^�̔j��(�I�u�W�F�N�g�Ǘ��N���X�p)
	* @param	void
	* @return	void
	*/
	void DestroyObjectManager(void);

	//�ȉ��{���̍X�V���s ���[�N���̃`�F�b�N�̂��߂ɂ���ɃX�R�[�v��p�ӂ���

	/**
	*	���ۂ̍X�V
	*	@param	void
	*	@return	void
	*/
	void UpdateExec(void);

	/**
	*	���ۂ̕`��
	*	@param	void
	*	@return	void
	*/
	void DrawExec(void);

private:

};
#endif
//End of File _SCENEDEMO_H_