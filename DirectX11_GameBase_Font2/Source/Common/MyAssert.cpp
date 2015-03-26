//==============================================================================
// File		Assert.cpp
// Comment	アサートヘッダファイル
// Author	TOMOHIRO KOUNO
// Create	2014/1/4
//==============================================================================

/*------------------------------------------------------------------------------
//	インクルード
------------------------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS

#include "MyAssert.h"

void MyAssert(TCHAR *pExp, TCHAR *pFileName, int nLine, TCHAR *pFormat, ...)
{
	const int STRSIZE = 512;
	TCHAR	aStr[ STRSIZE ];		// 表示文字列
	TCHAR aStrResult[STRSIZE];		// 最終結果文字列
	va_list	args;					// 引数

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

	// 表示文字列作成
	va_start( args, pFormat );
	_vsntprintf(aStr,_TRUNCATE, pFormat, args);
	va_end( args );

	//TCHAR変換によって文字列が壊れるので事前に取った控えを表示
	_stprintf(aStrResult, _T("!!!!ASSERT ERROR!!!! \nExpressinon %s,\nMessage <%s>\nErrorFile:%s=> Line:%d\n"), aDispExp, &aStr[0], aDispFileName, nDispLine);

	//出力実行！
	/*後はここをprintfにするかWinmessageにするかの違いくらいしかない*/
	//printf("!!!!ASSERT ERROR!!!! \nExpressinon %s,Message <%s>\nErrorFile:%s=> Line:%d\n",pExp,&aStr[ 0 ],pFileName,nLine);

	//デバッガに出力することでエラー文のコピーペーストが出来る。
	#ifdef OUTPUT_ASSERT_STRING
	OutputDebugString(&aStrResult[0]);
	#endif

	//メッセージボックスに出すとプログラマにとって、状況を把握しやすい
	#ifdef OUTPUT_ASSERT_BOX
	MessageBox(NULL, &aStrResult[0], _T("ASSERT ERROR"), MB_OK);
	#endif
}
//End of File