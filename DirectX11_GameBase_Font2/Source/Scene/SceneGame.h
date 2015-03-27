//==============================================================================
// File		SceneGame.h
// Comment	�^�C�g����ʃN���X
// Author	TOMOHIRO KOUNO
// Create	2014�N7��10��
//==============================================================================

//------------------------------------------------------------------------------
//	�C���N���[�h�K�[�h
//------------------------------------------------------------------------------
#ifndef _SCENEGAME_H_
#define _SCENEGAME_H_

//------------------------------------------------------------------------------
//	�C���N���[�h
//------------------------------------------------------------------------------
#include "SceneBase.h"

//------------------------------------------------------------------------------
//	�O���錾
//------------------------------------------------------------------------------
class CSprite;
class CHuman;
class CFontString;

/**
* @brief �^�C�g����ʃN���X
*/
class CSceneGame :public CSceneBase
{
public:

	/**
	* @brief Constructor
	* @param	void
	* @return	void
	*/
	CSceneGame(void);

	/**
	* @brief Destructor
	*/
	virtual ~CSceneGame(void);

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
	*	���ۂ̍X�V(���������[�N�������ɏ�����悤�Ɋ֐����������Ă܂�)
	*	@param	void
	*	@return	void
	*/
	void UpdateExec(void);

	/**
	*	���ۂ̕`��(���������[�N�������ɏ�����悤�Ɋ֐����������Ă܂�)
	*	@param	void
	*	@return	void
	*/
	void DrawExec(void);

	/**
	*	�X�R�A�X�V����
	*	@param void
	*	@return void
	*/
	void UpdateScore();

private:
	
	CSprite* m_pBG;	//! �w�i
	CHuman** m_ppHuman; //! �l��

	int m_nScorePoint;
	CFontString* m_pScoreString; //! �X�R�A�\���p������
};
#endif
//End of File _SCENEGame_H_