//==============================================================================
// File		FontTexture.h
// Comment	DirectXフォント1文字テクスチャ生成処理
// Author	TOMOHIRO KOUNO
// Create	2015年3月13日
//==============================================================================

//------------------------------------------------------------------------------
// インクルードガード
//------------------------------------------------------------------------------
#pragma once
#ifndef _FONTTEXTURE_H_
#define _FONTTEXTURE_H_

//------------------------------------------------------------------------------
// インクルード
//------------------------------------------------------------------------------
#include <d3dx11.h>

/**
* @brief DirectX11 フォント1文字テクスチャ生成クラス
*/
class FontTexture
{
public:

	static const int MAX_CHAR_SIZE = 512; ///> フォントテクスチャに格納する最大認識文字数

	typedef struct DATA_TAG
	{
		ID3D11ShaderResourceView* m_pTextureResource;	///> 対応するテクスチャ情報
		UINT m_charCode;								///> 格納文字列
	} DATA;

	/**
	* @brief	Constructor
	* @param	void
	* @return	void
	*/
	FontTexture();

	/**
	* @brief Destructor
	*/
	~FontTexture();

	/**
	*	文字列情報に対応する文字テクスチャの作成(重複時は内部で回避します)
	*	@param	文字コード
	*	@param	文字のサイズ
	*	@return	DirectX11に対応したシェーダに送るためのテクスチャポインタ
	*/
	ID3D11ShaderResourceView* Create(TCHAR* c, int fontSize);

private:
	void CreateHDCAndFontOnce(int fontSize);///> 一度だけフォントとHDCコンテキストを用意
	static LOGFONT	m_LogFont;				///> フォント用のデータ構造体
	static HFONT	m_HFont;				///> 描画用フォントハンドル
	static HFONT	m_OldFont;				///> 交換用のフォントハンドル
	static HDC		m_HDC;					///> Windows用の描画ハンドル
	static bool		m_Once;					///> クラス一回処理用フラグ
	static DATA		m_Datas[512];			///> 格納情報構造体
};
#endif
// End of File _FONTTEXTURE_H_