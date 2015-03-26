//==============================================================================
// File		System.h
// Comment	�����V�X�e���ŋ��ʂɌp������N���X���܂Ƃ߂�����
// Author	TOMOHIRO KOUNO
// Create	2014�N6��15��
//==============================================================================

//------------------------------------------------------------------------------
//	�C���N���[�h�K�[�h
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