//==============================================================================
// File		Object2D.h
// Comment	2D�I�u�W�F�N�g���N���X
// Author	TOMOHIRO KOUNO
// Create	2014�N12��31��
//==============================================================================

//------------------------------------------------------------------------------
// �C���N���[�h�K�[�h
//------------------------------------------------------------------------------
#pragma once
#ifndef _OBJECT2D_H_
#define _OBJECT2D_H_

//------------------------------------------------------------------------------
// �C���N���[�h�t�@�C��
//------------------------------------------------------------------------------
#include "Object2D.h"

class CObject2DHuman
{
public:
	CObject2DHuman(void){}

	~CObject2DHuman(void){}

	virtual void Update(void){}

	virtual void ShaderDraw(void){}

	virtual void Draw(void){}

};
#endif 
//End of File _OBJECT_2D_