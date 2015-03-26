//==============================================================================
// File		Vertex.h
// Comment	���_�N���X
// Author	TOMOHIRO KOUNO
// Create	2014�N12��31��
//==============================================================================

//------------------------------------------------------------------------------
// �C���N���[�h�K�[�h
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
