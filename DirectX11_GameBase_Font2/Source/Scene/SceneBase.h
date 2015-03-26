//==============================================================================
// File		SceneBase.h
// Comment	シーン遷移抽象クラス
// Author	TOMOHIRO KOUNO
// Create	2014年7月10日
//==============================================================================

//------------------------------------------------------------------------------
//	インクルードガード
//------------------------------------------------------------------------------
#ifndef _SCENEBASE_H_
#define _SCENEBASE_H_

/**
* @brief シーン遷移抽象クラス
*/
class CSceneBase
{
public:
	/**
	* @brief Constructor
	* @param	void
	* @return	void
	*/
	CSceneBase(void){}

	/**
	* @brief Destructor
	*/
	virtual ~CSceneBase(void){}

	/**
	*	Update Pure Fuction
	*	@param	void
	*	@return	void
	*/
	virtual void Update(void) = 0;

	/**
	*	Draw Pure Fuction
	*	@param	void
	*	@return	void
	*/
	virtual void Draw(void) = 0;

	/**
	*	Save GameObject Scene
	*	@param	void
	*	@return	void
	*/
	virtual void Save(void){}

	/**
	*	Load GameObject Scene
	*	@param	void
	*	@return	void
	*/
	virtual void Load(void){}

private:
	
};
#endif
//End of File _SCENEBASE_H_