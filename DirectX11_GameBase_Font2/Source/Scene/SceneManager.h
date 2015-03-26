//==============================================================================
// File		SceneManager.h
// Comment	�V�[���Ǘ��N���X
// Author	TOMOHIRO KOUNO
// Create	2014�N7��11��
//==============================================================================

//------------------------------------------------------------------------------
//	�C���N���[�h�K�[�h
//------------------------------------------------------------------------------
#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

//------------------------------------------------------------------------------
//	�C���N���[�h
//------------------------------------------------------------------------------
#include "SceneLogo.h"
#include "SceneTitle.h"
#include "SceneDemo.h"
#include "SceneGame.h"
#include "SceneResult.h"
#include "SceneRanking.h"
#include "SceneGameOver.h"

//------------------------------------------------------------------------------
//	�O���Q��
//------------------------------------------------------------------------------
class CSceneBase;
/**
* @brief �V�[���Ǘ��N���X
*/
class CSceneManager :public ISystem
{
public:

	enum SCENE_TYPE
	{
		SCENE_TYPE_LOGO,
		SCENE_TYPE_TITLE,
		SCENE_TYPE_DEMO,
		SCENE_TYPE_GAME,
		SCENE_TYPE_RESULT,
		SCENE_TYPE_RANKING,
		SCENE_TYPE_GAMEOVER,
	};

	/**
	* @brief Constructor
	* @param	void
	* @return	void
	*/
	CSceneManager(void);

	/**
	* @brief Destructor
	*/
	~CSceneManager(void);

	/**
	*	�I��
	*	@param	void
	*	@return	void
	*/
	void Finalize(void);

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
	*	�J�ڏ������s
	*	@param	void
	*	@return	void
	*/
	void Change(void);

	/**
	*	����V�[�����ēǂݍ��݂���
	*	@param	void
	*	@return	void
	*/
	void ReloadScene(void);

	/**
	*	�V�[���̑J��
	*	@param	Type	�J�ڂ������V�[���ւ̃^�C�v
	*	@return	void
	*/
	void GotoScene(SCENE_TYPE Type);

	/**
	*	���݊Ǘ��V�[���̕ԋp
	*	@param	void
	*	@return	m_pScene		���݂̃V�[�����
	*/
	CSceneBase* GetCurrentScene(void);

	/**
	*	���݊Ǘ��V�[���^�C�v�̕ԋp
	*	@param	void
	*	@return	m_pScene		���݂̃V�[���^�C�v���
	*/
	SCENE_TYPE GetCurrentSceneType(void);

private:
	CSceneBase *m_pScene;		///>	���݂̃V�[��
	CSceneBase *m_pSceneNext;	///>	����̃V�[��
	SCENE_TYPE  m_SceneType;	///>	���݃V�[���̃^�C�v
	SCENE_TYPE  m_SceneTypeNext;///>	����̃V�[���^�C�v
	bool	    m_bReloadScene;	///>	�����V�[�����J��Ԃ��ǂݍ��ރt���O
};
#endif
//End of File _SCENEMANAGER_H_