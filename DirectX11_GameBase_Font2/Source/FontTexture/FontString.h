//==============================================================================
// File		FontString.h
// Comment	DirectXフォント文字列描画
// Author	TOMOHIRO KOUNO
// Create	2015年3月15日
//==============================================================================

//==============================================================================
// 注意点
// DirectX11での自然なフォント作成処理には大規模な工数が必要になるため、
// 現在は利用方法に制限を持たせることにしました。
// 具体的には以下に示す制限です。
// [1]:基本的にはデバッグ用途です。必ず更新を呼んでから文字列を追加してください。
// [2]:文字列の再利用によるキャッシュをDirectX11では強制されるため
//     テクスチャマネージャなどに非依存なキャッシュ機能を付与しています。
// [3]:現在は@マークを初期化用のマークに利用してます。
//==============================================================================

//------------------------------------------------------------------------------
// インクルードガード
//------------------------------------------------------------------------------
#pragma once
#ifndef _FONTSTRING_H_
#define _FONTSTRING_H_

//------------------------------------------------------------------------------
// インクルード
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// 前方宣言
//------------------------------------------------------------------------------
class FontTexture;
class CSprite;

/**
* @brief DirectX11 文字列描画クラス
*/
class CFontString
{
public:
	static const u16 MAX_FONT_DISP_SIZE = 1024;		///> 文字列の表示限界数
	static const u8 OFFSET_X			= 32;		///> 文字間隔X
	static const u8 OFFSET_Y			= 32;		///> 文字間隔Y
	static const u16 BUFFER_MAX			= 1024;		///> 文字列解析用のバッファ限界

	/**
	* @brief	Constructor
	* @param	void
	* @return	void
	*/
	CFontString(void);

	/**
	* @brief Destructor
	*/
	~CFontString(void);

	/**
	*	更新
	*	@param	void
	*	@return	void
	*/
	void Update(void);

	/**
	*	描画
	*	@param	void
	*	@return	void
	*/
	void Draw(void);

	/**
	*	文字の表示
	*	@param	文字列フォーマット
	*	@return	void
	*/
	void printfString(const TCHAR* format, ...);
	void printfString(const XMFLOAT2& pos,const TCHAR* format, ...);

	/**
	*	現在の描画色を変更する
	*	@param	void
	*	@return	void
	*/
	void SetColor(const XMFLOAT4& color);

private:
	TString			m_Text;											///> Unicode 対応ストリング
	FontTexture**	m_pFontTextures		= nullptr;					///> テクスチャ用データポインタ配列
	CSprite**		m_pSprites			= nullptr;					///> 描画用2Dポリゴンポインタ配列
	int				m_UseTextNum		= 0;						///> 現在描画文字列数
	XMFLOAT2		m_Position			= XMFLOAT2(0, 0);			///> 現在描画位置
	XMFLOAT4		m_Color				= XMFLOAT4(1, 1, 1, 1);		///> 現在描画色
};
#endif
//End of File _FONTSTRING_H_