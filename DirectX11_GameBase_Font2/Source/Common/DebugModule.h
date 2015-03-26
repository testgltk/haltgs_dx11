//==============================================================================
// File		DebugModule.h
// Comment	�f�o�b�O�p�v���O����
// Author	TOMOHIRO KOUNO
// Create	2014�N6��15��
//==============================================================================

//------------------------------------------------------------------------------
// �C���N���[�h�K�[�h
//------------------------------------------------------------------------------
#pragma once
#ifndef _DEBUG_MODULE_H_
#define _DEBUG_MODULE_H_

/**
* ���b�Z�[�W�{�b�N�X�\��
* @param	�����t�H�[�}�b�g
* @return	void
*/
void MSGBOX(TCHAR *Text, ...);

/**
* ���b�Z�[�W�{�b�N�X�\��(YES OR NO)
* @param	�����t�H�[�}�b�g
* @return	YES OR NO 
*/
int YESNO(TCHAR *Text, ...);

/**
* �x���\��
* @param	�����t�H�[�}�b�g
* @return	void
*/
void WARRNING(TCHAR *Text, ...);

/**
* �f�o�b�K�o��
* @param	�����t�H�[�}�b�g
* @return	void
*/
void OUTPUT(TCHAR *Text, ...);

/**
* �t�@�C�����݊m�F
* @param	�t�@�C���p�X
* @return	TRUE  : �t�@�C���L��
* @return	FALSE : �t�@�C������
*/
bool FILECHECK(TCHAR *FilePath);

/**
* �t�@�C�����݊m�F
* @param	�t�@�C���p�X
* @return	TRUE  : �t�@�C���L��
* @return	FALSE : �t�@�C������
*/
bool FILECHECK(TString FilePath);

#endif
