//==============================================================================
// File		Singleton.h
// Comment	シングルトンテンプレートユーティリティ
// Author	TOMOHIRO KOUNO
// Create	2014年7月9日
//==============================================================================

//------------------------------------------------------------------------------
//	インクルードガード
//------------------------------------------------------------------------------
#ifndef _SINGLETON_H_
#define _SINGLETON_H_

/**
* @brief シングルトンテンプレートユーティリティ
*/
template <class T>
class CSingleton
{
public:

	/**
	*	Create Object Once
	*	@param	void
	*	@return	void
	*/
	static void Create(void)
	{
		if(_instance == nullptr)
		{
			_instance = new T();
		}
	}

	
	/**
	*	Create Destroy Once
	*	@param	void
	*	@return	void
	*/
	static void Destroy(void)
	{
		if(_instance != nullptr)
		{
			delete _instance;
		}
	}

	/**
	*	return Insatnce
	*	@param	void
	*	@return	void
	*/
	static T* Instance(void)
	{
		return _instance;
	}

private:
	// 禁止
	CSingleton() {}
	virtual ~CSingleton() {}
	CSingleton(const CSingleton&);
	CSingleton& operator=(const CSingleton&);
	static T* _instance;
public:



};
#endif

template<class T>
T* CSingleton<T>::_instance = nullptr;
//End of File _SINGLETON_H_