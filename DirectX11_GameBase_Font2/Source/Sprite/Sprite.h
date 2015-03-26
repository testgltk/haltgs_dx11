//==============================================================================
// File		Sprite.h
// Comment	2Dポリゴン表示クラス
// Author	TOMOHIRO KOUNO
// Create	2014年12月31日
//==============================================================================

//------------------------------------------------------------------------------
// インクルードガード
//------------------------------------------------------------------------------
#pragma once
#ifndef _SPRITE_H_
#define _SPRITE_H_

//------------------------------------------------------------------------------
// インクルード
//------------------------------------------------------------------------------
#include "Object/Object2D.h"

class CSprite : public CObject2D
{
public:

	typedef enum ALIGN_TAG
	{
		ALIGN_LEFT_TOP,
		ALIGN_CENTER
	}ALIGN;

	typedef struct PARAM_TAG
	{
		XMFLOAT2	m_Position;
		float		m_Rotation;
		TString		m_TextureName;
	}PARAM;


	explicit CSprite(const PARAM& param);
			 CSprite(void);
	virtual ~CSprite(void);

	void Update(void);
	void Draw(void);
	void Finalize(void);

	void SetPosition(const XMFLOAT2& pos);
	void SetRotation(float Rotation);
	void SetPolygonAlign(ALIGN align);
	void SetWidth(float Width);
	void SetHeight(float Height);
	void SetColor(const XMFLOAT4& color);
	void SetTexture(ID3D11ShaderResourceView* pTextureResource);
	void SetTextureUnsafeFont(ID3D11ShaderResourceView* pTextureResource);
	void SetTextureNone(void);

	XMFLOAT2 GetPosition(void);
	float GetWidth(void);
	float GetHeight(void);

private:
	HRESULT CreateShader(void);
	HRESULT CreatePolygon(void);

	static ID3D11VertexShader*	m_pVertexShader;
	static ID3D11PixelShader*	m_pPixelShader;
	static ID3D11InputLayout*	m_pVertexLayout;
	static ID3D11Buffer*		m_pConstantBuffer;

	ID3D11Buffer*				m_pVertexBuffer		= nullptr;
	ID3D11ShaderResourceView*	m_pShaderResView	= nullptr;
	
	XMFLOAT2					m_Position;
	float						m_Rotation			= 0.0f;
	float						m_Width				= 0.0f;
	float						m_Height			= 0.0f;
	ALIGN						m_Align				= ALIGN_CENTER;
	TString						m_TextureName;
};
#endif 
//End of File _SPRITE_H_