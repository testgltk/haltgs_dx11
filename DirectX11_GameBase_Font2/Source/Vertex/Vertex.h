//==============================================================================
// File		Vertex.h
// Comment	頂点クラス
// Author	TOMOHIRO KOUNO
// Create	2014年12月31日
//==============================================================================

//------------------------------------------------------------------------------
// インクルードガード
//------------------------------------------------------------------------------
#pragma once
#ifndef _VERTEX_H_
#define _VERTEX_H_

struct Vertex3D
{
	XMFLOAT3 Position;
	XMFLOAT4 Color;
	XMFLOAT2 TexCoord;
};


struct ConstantBuffer
{
	XMMATRIX WorldViewProjection;
};

#endif
