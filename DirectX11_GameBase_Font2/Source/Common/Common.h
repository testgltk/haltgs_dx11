//==============================================================================
// File		Common.h
// Comment	ここにインクルードしたものは全ての
//			場所でも自動的にインクルードされます
//			stdafx.hに含ませないようにしておくこと。
//			含ませるとプロジェクトをテンプレートデータ化できなくなってしまいます
// Author	TOMOHIRO KOUNO
// Create	2014年6月15日
//==============================================================================

//------------------------------------------------------------------------------
//	インクルードガード
//------------------------------------------------------------------------------
#pragma once
#ifndef _COMMON_H_
#define _COMMON_H_

//------------------------------------------------------------------------------
//	インクルード
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