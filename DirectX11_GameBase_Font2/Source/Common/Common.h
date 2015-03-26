//==============================================================================
// File		Common.h
// Comment	�����ɃC���N���[�h�������̂͑S�Ă�
//			�ꏊ�ł������I�ɃC���N���[�h����܂�
//			stdafx.h�Ɋ܂܂��Ȃ��悤�ɂ��Ă������ƁB
//			�܂܂���ƃv���W�F�N�g���e���v���[�g�f�[�^���ł��Ȃ��Ȃ��Ă��܂��܂�
// Author	TOMOHIRO KOUNO
// Create	2014�N6��15��
//==============================================================================

//------------------------------------------------------------------------------
//	�C���N���[�h�K�[�h
//------------------------------------------------------------------------------
#pragma once
#ifndef _COMMON_H_
#define _COMMON_H_

//------------------------------------------------------------------------------
//	�C���N���[�h
//------------------------------------------------------------------------------
#include "SafeCheck.h"
#include "type_alias.h"
#include "MyAssert.h"
#include "Singleton.h"
#include "Random.h"
#include "DebugModule.h"
#include "MathUtility.h"
#include "ConstantTable.h"
#include "Input/InputKeyboard.h"
#include "Input/InputJoypad.h"
#include "Input/InputXInput.h"
#include "Input/InputMouse.h"
#include "Vertex/Vertex.h"

HINSTANCE GetHinstance(void);
HWND GetHWnd(void);
void SetHinstance(HINSTANCE hInstance);
void SetHWnd(HWND hWnd);

#endif
// End of File _COMMON_H_