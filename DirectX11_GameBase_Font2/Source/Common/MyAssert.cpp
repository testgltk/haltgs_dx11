//==============================================================================
// File		Assert.cpp
// Comment	�A�T�[�g�w�b�_�t�@�C��
// Author	TOMOHIRO KOUNO
// Create	2014/1/4
//==============================================================================

/*------------------------------------------------------------------------------
//	�C���N���[�h
------------------------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS

#include "MyAssert.h"

void MyAssert(TCHAR *pExp, TCHAR *pFileName, int nLine, TCHAR *pFormat, ...)
{
	const int STRSIZE = 512;
	TCHAR	aStr[ STRSIZE ];		// �\��������
	TCHAR aStrResult[STRSIZE];		// �ŏI���ʕ�����
	va_list	args;					// ����

	TCHAR aDispExp[STRSIZE];
	TCHAR aDispFileName[STRSIZE];
	TCHAR aDispFormat[STRSIZE];
	int   nDispLine = nLine;
	
	ZeroMemory(aStr, sizeof(aStr));
	ZeroMemory(aStrResult, sizeof(aStrResult));
	ZeroMemory(aDispExp, sizeof(aDispExp));
	ZeroMemory(aDispFileName, sizeof(aDispFileName));
	ZeroMemory(aDispFormat, sizeof(aDispFormat));

	_tcscpy(aDispExp, pExp);
	_tcscpy(aDispFileName, pFileName);
	_tcscpy(aDispFormat, pFormat);

	// �\��������쐬
	va_start( args, pFormat );
	_vsntprintf(aStr,_TRUNCATE, pFormat, args);
	va_end( args );

	//TCHAR�ϊ��ɂ���ĕ����񂪉���̂Ŏ��O�Ɏ�����T����\��
	_stprintf(aStrResult, _T("!!!!ASSERT ERROR!!!! \nExpressinon %s,\nMessage <%s>\nErrorFile:%s=> Line:%d\n"), aDispExp, &aStr[0], aDispFileName, nDispLine);

	//�o�͎��s�I
	/*��͂�����printf�ɂ��邩Winmessage�ɂ��邩�̈Ⴂ���炢�����Ȃ�*/
	//printf("!!!!ASSERT ERROR!!!! \nExpressinon %s,Message <%s>\nErrorFile:%s=> Line:%d\n",pExp,&aStr[ 0 ],pFileName,nLine);

	//�f�o�b�K�ɏo�͂��邱�ƂŃG���[���̃R�s�[�y�[�X�g���o����B
	#ifdef OUTPUT_ASSERT_STRING
	OutputDebugString(&aStrResult[0]);
	#endif

	//���b�Z�[�W�{�b�N�X�ɏo���ƃv���O���}�ɂƂ��āA�󋵂�c�����₷��
	#ifdef OUTPUT_ASSERT_BOX
	MessageBox(NULL, &aStrResult[0], _T("ASSERT ERROR"), MB_OK);
	#endif
}
//End of File