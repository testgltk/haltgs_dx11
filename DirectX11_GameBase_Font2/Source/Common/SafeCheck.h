//==============================================================================
// File		SafeCheck.h
// Comment	テンプレート等の便利機能をまとめたもの
// Author	TOMOHIRO KOUNO
// Create	2014年6月15日
//==============================================================================

//------------------------------------------------------------------------------
//	インクルードガード
//------------------------------------------------------------------------------
#pragma once
#ifndef _SAFECHECK_H_
#define _SAFECHECK_H_

template<typename T>
inline void SafeRelease(T*& pRelease)
{
	if (pRelease != nullptr)
	{
		pRelease->Release();
		pRelease = nullptr;
	}
}

template<typename T>
inline void SafeDelete(T*& pDelete)
{
	if (pDelete != nullptr)
	{
		delete (pDelete);
		(pDelete) = nullptr;
	}
}

template<typename T>
inline void SafeDeleteArray(T*& pDelete)
{
	if (pDelete != nullptr)
	{
		delete[](pDelete);
		(pDelete) = nullptr;
	}
}

template<typename T>
inline void SafeFinalize(T*& pFinalize)
{
	if (pFinalize != nullptr)
	{
		pFinalize->Finalize();
		delete (pFinalize);
		pFinalize = nullptr;
	}
}

#endif