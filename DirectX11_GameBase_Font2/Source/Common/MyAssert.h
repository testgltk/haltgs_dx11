//==============================================================================
// File		Assert.h
// Comment	�A�T�[�g�w�b�_�t�@�C��
// Author	TOMOHIRO KOUNO
// Create	2014/1/4
//==============================================================================

//------------------------------------------------------------------------------
//	�C���N���[�h�K�[�h
//------------------------------------------------------------------------------
#pragma once
#ifndef _ASSERT_H_
#define _ASSERT_H_

//------------------------------------------------------------------------------
//	�C���N���[�h
//------------------------------------------------------------------------------
#include <stdarg.h>

//------------------------------------------------------------------------------
//	�}�N����`
//------------------------------------------------------------------------------
#define BLAKEPOINT __asm int 3/*�����I�u���[�N��������A�Z���u������*/
#define CUSTOM_ASSERT_ENABLE //�J�X�^���p�̃A�T�[�g�����邱�Ƃ��O���ɒm�点�Ă�����

//�J�X�^�}�C�Y�}�N��
//�K�v�ɉ����ā@�R�����g�A�E�g�������Đ؂�ւ��Ă��������B
#define OUTPUT_ASSERT_STRING //��`����Ă�ƃA�T�[�g�����f�o�b�K�̏o�͂ɂ͂��Ă���� 
#define OUTPUT_ASSERT_BOX	 //��`����Ă�ƃA�T�[�g����MessageBox�Œm�点��

//DO_ASSERT �Ɓ@DO_STORONG_ASSERT��
//�R�����g�A�E�g����Ƃ��ł��A�T�[�g�̗L���؂�ւ����ł���
#ifdef _DEBUG
#define DO_ASSERT
#endif

#define DO_STORONG_ASSERT

#ifdef DO_ASSERT
#define MYASSERT(exp,format,...) if (exp){}else{\
	MyAssert(_T(#exp),_T(__FILE__) ,int(__LINE__) ,_T(format) ,__VA_ARGS__);\
	BLAKEPOINT/*�u���[�N�|�C���g�Ăяo��*/\
}
#else
#define MYASSERT(exp,format,...) (exp)
#endif

#ifdef DO_STORONG_ASSERT
#define STRONG_ASSERT(exp,format,...) if (exp){}else{\
	MyAssert(#exp,__FILE__,__LINE__,format,__VA_ARGS__);\
	BLAKEPOINT/*�u���[�N�|�C���g�Ăяo��*/\
}
#else STRONG_ASSERT(exp,format,...)
#endif

//------------------------------------------------
// �������u���C�N�|�C���g
// ���������^�̎��Ƀu���C�N�|�C���g����������
// �J�����ˑ��̏������u���C�N�|�C���g�͏d�������肷��
// ex) BREAK_IF( i == 100 ) => �u���C�N�|�C���g����
//------------------------------------------------
#ifdef _DEBUG
#define BREAK_IF( exp ) { if( ( exp ) ) { __debugbreak(); } }
#else
#define BREAK_IF __noop
#endif

//------------------------------------------------------------------------------
//	�v���g�^�C�v�錾
//------------------------------------------------------------------------------
/**
*	�A�T�[�g�@�Ăяo������
*   @param  pExp ��
*   @param  pFileName �G���[�����t�@�C����
*   @param  nLine �G���[�s��
*   @param  pFormat �⑫��񕶎���
*   @return void
*/
void MyAssert(TCHAR *pExp, TCHAR *pFileName, int nLine, TCHAR *pFormat, ...);

#endif
//End of File�@_ASSERT_H_