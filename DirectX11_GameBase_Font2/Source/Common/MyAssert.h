//==============================================================================
// File		Assert.h
// Comment	アサートヘッダファイル
// Author	TOMOHIRO KOUNO
// Create	2014/1/4
//==============================================================================

//------------------------------------------------------------------------------
//	インクルードガード
//------------------------------------------------------------------------------
#pragma once
#ifndef _ASSERT_H_
#define _ASSERT_H_

//------------------------------------------------------------------------------
//	インクルード
//------------------------------------------------------------------------------
#include <stdarg.h>

//------------------------------------------------------------------------------
//	マクロ定義
//------------------------------------------------------------------------------
#define BLAKEPOINT __asm int 3/*強制的ブレーク発生特殊アセンブラ命令*/
#define CUSTOM_ASSERT_ENABLE //カスタム用のアサートがあることを外部に知らせてあげる

//カスタマイズマクロ
//必要に応じて　コメントアウト等をして切り替えてください。
#define OUTPUT_ASSERT_STRING //定義されてるとアサート文をデバッガの出力にはいてくれる 
#define OUTPUT_ASSERT_BOX	 //定義されてるとアサート文をMessageBoxで知らせる

//DO_ASSERT と　DO_STORONG_ASSERTを
//コメントアウトするといつでもアサートの有無切り替えができる
#ifdef _DEBUG
#define DO_ASSERT
#endif

#define DO_STORONG_ASSERT

#ifdef DO_ASSERT
#define MYASSERT(exp,format,...) if (exp){}else{\
	MyAssert(_T(#exp),_T(__FILE__) ,int(__LINE__) ,_T(format) ,__VA_ARGS__);\
	BLAKEPOINT/*ブレークポイント呼び出し*/\
}
#else
#define MYASSERT(exp,format,...) (exp)
#endif

#ifdef DO_STORONG_ASSERT
#define STRONG_ASSERT(exp,format,...) if (exp){}else{\
	MyAssert(#exp,__FILE__,__LINE__,format,__VA_ARGS__);\
	BLAKEPOINT/*ブレークポイント呼び出し*/\
}
#else STRONG_ASSERT(exp,format,...)
#endif

//------------------------------------------------
// 条件式ブレイクポイント
// 条件式が真の時にブレイクポイントが発生する
// 開発環境依存の条件式ブレイクポイントは重かったりする
// ex) BREAK_IF( i == 100 ) => ブレイクポイント発生
//------------------------------------------------
#ifdef _DEBUG
#define BREAK_IF( exp ) { if( ( exp ) ) { __debugbreak(); } }
#else
#define BREAK_IF __noop
#endif

//------------------------------------------------------------------------------
//	プロトタイプ宣言
//------------------------------------------------------------------------------
/**
*	アサート　呼び出し処理
*   @param  pExp 式
*   @param  pFileName エラーしたファイル名
*   @param  nLine エラー行数
*   @param  pFormat 補足情報文字列
*   @return void
*/
void MyAssert(TCHAR *pExp, TCHAR *pFileName, int nLine, TCHAR *pFormat, ...);

#endif
//End of File　_ASSERT_H_