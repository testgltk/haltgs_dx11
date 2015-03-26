//==============================================================================
// File		Renderer.h
// Comment	�����_���N���X
// Author	TOMOHIRO KOUNO
// Create	2014�N12��31��
//==============================================================================

//------------------------------------------------------------------------------
// �C���N���[�h�K�[�h
//------------------------------------------------------------------------------
#pragma once
#ifndef _RENDERER_H_
#define _RENDERER_H_

//------------------------------------------------------------------------------
// �C���N���[�h
//------------------------------------------------------------------------------
class CRenderer : public ISystem
{
public :
	CRenderer(void);
	~CRenderer(void);

	void Initilalize(void);
	void Update(void);
	void Finalize(void);

	void Clear(void);
	void Present(void);
	void SetDefaultRenderState(void);

	ID3D11Device*			GetDevice(void);
	ID3D11DeviceContext*	GetDeviceContext(void);
private:
	D3D_FEATURE_LEVEL		m_FeatureLevel		= D3D_FEATURE_LEVEL_11_0;
	ID3D11Device*			m_pD3DDevice		= nullptr;
	ID3D11DeviceContext*	m_pImmediateContext = nullptr;
	IDXGISwapChain*			m_pSwapChain		= nullptr;
	ID3D11RenderTargetView* m_pRenderTargetView = nullptr;
};
#endif
// End of File _RENDERER_H_