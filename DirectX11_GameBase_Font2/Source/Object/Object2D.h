//==============================================================================
// File		Object2D.h
// Comment	2Dオブジェクト基底クラス
// Author	TOMOHIRO KOUNO
// Create	2014年12月31日
//==============================================================================

//------------------------------------------------------------------------------
// インクルードガード
//------------------------------------------------------------------------------
#pragma once
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

class CObject2D
{
public:
	CObject2D(void){}
	virtual ~CObject2D(void){}

	virtual void Update(void) = 0;

	virtual void ShaderDraw(void){}

	virtual void Draw(void) = 0;

};
#endif 
//End of File _OBJECT_2D_