//==============================================================================
// File		System.h
// Comment	内部システムで共通に継承するクラスをまとめたもの
// Author	TOMOHIRO KOUNO
// Create	2014年6月15日
//==============================================================================

//------------------------------------------------------------------------------
//	インクルードガード
//------------------------------------------------------------------------------
#pragma once
#ifndef _SYSTEM_H_
#define _SYSTEM_H_

class ISystem
{
public:
	ISystem(void){}
	virtual ~ISystem(void){}

	virtual void Update(void) = 0;
	virtual void Finalize(void) = 0;
private:
};

class IGraphics
{
public:
	IGraphics(void){}
	virtual ~IGraphics(void){}

	virtual void Update(void) = 0;
	virtual void ShaderPreDraw(void){}
	virtual void Draw(void) = 0;
	virtual void Finalize(void) = 0;
private:
};



#endif