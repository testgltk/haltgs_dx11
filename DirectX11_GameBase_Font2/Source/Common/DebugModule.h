//==============================================================================
// File		DebugModule.h
// Comment	デバッグ用プログラム
// Author	TOMOHIRO KOUNO
// Create	2014年6月15日
//==============================================================================

//------------------------------------------------------------------------------
// インクルードガード
//------------------------------------------------------------------------------
#pragma once
#ifndef _DEBUG_MODULE_H_
#define _DEBUG_MODULE_H_

/**
* メッセージボックス表示
* @param	文字フォーマット
* @return	void
*/
void MSGBOX(TCHAR *Text, ...);

/**
* メッセージボックス表示(YES OR NO)
* @param	文字フォーマット
* @return	YES OR NO 
*/
int YESNO(TCHAR *Text, ...);

/**
* 警告表示
* @param	文字フォーマット
* @return	void
*/
void WARRNING(TCHAR *Text, ...);

/**
* デバッガ出力
* @param	文字フォーマット
* @return	void
*/
void OUTPUT(TCHAR *Text, ...);

/**
* ファイル存在確認
* @param	ファイルパス
* @return	TRUE  : ファイル有り
* @return	FALSE : ファイル無し
*/
bool FILECHECK(TCHAR *FilePath);

/**
* ファイル存在確認
* @param	ファイルパス
* @return	TRUE  : ファイル有り
* @return	FALSE : ファイル無し
*/
bool FILECHECK(TString FilePath);

#endif
