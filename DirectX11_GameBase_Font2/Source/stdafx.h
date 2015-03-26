//==============================================================================
// File		stdafx.h
// Comment	�v���R���p�C���ς݃w�b�_�[�t�@�C��
// Author	TOMOHIRO KOUNO
// Create	2014�N1��31��
//==============================================================================

//------------------------------------------------------------------------------
//	�C���N���[�h�K�[�h
//------------------------------------------------------------------------------
#ifndef _STDAFX_H_
#define _STDAFX_H_

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include <stdlib.h>
#include <crtdbg.h>
#endif

//------------------------------------------------------------------------------
//	�W�����C�u�����C���N���[�h
//------------------------------------------------------------------------------
#define  _CRT_SECURE_NO_WARNINGS
#define  _CRT_NON_CONFORMING_SWPRINTFS
#define WIN32_LEAN_AND_MEAN  // Windows �w�b�_�[����g�p����Ă��Ȃ����������O���܂��B
#include <Windows.h>
//#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <process.h>
#include <MMsystem.h>
#include <tchar.h>
#include <locale>

//------------------------------------------------
// C++ �V�X�e���t�@�C��
//------------------------------------------------
#include <iostream>

//------------------------------------------------
// C++ STL
//------------------------------------------------
// STL�̃f�o�b�O�@�\��OFF�ɂ���
#ifndef _SECURE_SCL
#define _SECURE_SCL (0)
#endif
#ifndef _HAS_ITERATOR_DEBUGGING
#define _HAS_ITERATOR_DEBUGGING (0)
#endif
#ifndef  _ITERATOR_DEBUG_LEVEL
#define  _ITERATOR_DEBUG_LEVEL 0
#endif
#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>
#include <algorithm>

typedef std::basic_string<TCHAR> TString;

//------------------------------------------------
// C++ 2013
//------------------------------------------------
#include <chrono>

//------------------------------------------------------------------------------
//	�O���t�B�b�N�X���C�u�����C���N���[�h
//------------------------------------------------------------------------------
#ifdef _DEBUG
#include <DxErr.h>
#endif
//#include "d3d9.h"
//#include "d3dx9.h"

//����ĂȂ���SSE��Ή���PC���������ꍇ�ɂ�����B��̓I�ɂ�
//XMAMATRIX,XMQUTANION�n���̊|���Z���ԁA����Ȃǂ�SSE���߂ŃG���[
#define _XM_NO_INTRINSICS_ 

//#include <d3d11.h>
#include <d3dX11.h>
#include <d3dcompiler.h>
#include <D2d1.h>
#include <DWrite.h>
#include <xnamath.h>
//------------------------------------------------------------------------------
//	�C���v�b�g���C�u�����C���N���[�h
//------------------------------------------------------------------------------
#define DIRECTINPUT_VERSION (0x0800)    // �x���΍��p
#include "XInput.h"
#include <dinput.h>

//------------------------------------------------------------------------------
//	�T�E���h���C�u�����C���N���[�h
//------------------------------------------------------------------------------
#include "xaudio2.h"
#include <xact3.h>
#include <xact3d3.h>

//------------------------------------------------------------------------------
// ���C�u�����̃����N
//------------------------------------------------------------------------------
#pragma comment (lib,"d3d11.lib")
#pragma comment (lib,"d3dx11d.lib")
#pragma comment (lib, "d3dcompiler.lib")
#pragma comment (lib,"DWrite.lib")
#pragma comment (lib,"D2d1.lib")
#pragma comment (lib,"dxguid.lib")
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "Xinput.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "X3daudio.lib")

//------------------------------------------------------------------------------
// �}�N����`
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
//	���������[�N���o
//------------------------------------------------------------------------------
#define _CRTDBG_MAP_ALLOC

#ifdef _DEBUG
#include <stdlib.h>
#include <crtdbg.h>
#define   new                   new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define   malloc(s)             _malloc_dbg(s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   calloc(c, s)          _calloc_dbg(c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   realloc(p, s)         _realloc_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _recalloc(p, c, s)    _recalloc_dbg(p, c, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#define   _expand(p, s)         _expand_dbg(p, s, _NORMAL_BLOCK, __FILE__, __LINE__)
#endif

#endif