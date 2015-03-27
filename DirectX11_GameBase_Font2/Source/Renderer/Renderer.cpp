//==============================================================================
// File		Renderer.cpp
// Comment	レンダラクラス
// Author	TOMOHIRO KOUNO
// Create	2014年12月31日
//==============================================================================

//------------------------------------------------------------------------------
// インクルード
//------------------------------------------------------------------------------
#include "Renderer.h"
//#include "DirectXTK/SpriteFont.h"

IDWriteFactory* pWriteFactory_;
IDWriteTextFormat* pFom = NULL;
//ファクトリ 
ID2D1Factory* pD2DFactory;
//レンダーターゲット 
ID2D1HwndRenderTarget* pHwndRenderTarget;
ID2D1SolidColorBrush* pGreenBrush = NULL;

CRenderer::CRenderer(void)
{
	Initilalize();
}

CRenderer::~CRenderer(void)
{

}

void CRenderer::Initilalize(void)
{
	using namespace ns_ConstantTable;

	HRESULT hr;

	// デバイス、スワップチェーン、コンテキスト生成
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferCount = 1;
	sd.BufferDesc.Width = SCREEN_WIDTH;
	sd.BufferDesc.Height = SCREEN_HEIGHT;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = GetHWnd();
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;

	hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_WARP,
		NULL,
		D3D11_CREATE_DEVICE_DEBUG,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&m_pSwapChain,
		&m_pD3DDevice,
		&m_FeatureLevel,
		&m_pImmediateContext);
	if (FAILED(hr))
		return;

	// レンダーターゲットビュー生成、設定
	ID3D11Texture2D* pBackBuffer = NULL;
	m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);
	m_pD3DDevice->CreateRenderTargetView(pBackBuffer, NULL, &m_pRenderTargetView);
	pBackBuffer->Release();
	m_pImmediateContext->OMSetRenderTargets(1, &m_pRenderTargetView, NULL);

	// ビューポート設定
	D3D11_VIEWPORT vp;
	vp.Width = (FLOAT)SCREEN_WIDTH;
	vp.Height = (FLOAT)SCREEN_HEIGHT;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	m_pImmediateContext->RSSetViewports(1, &vp);

	//レンダーステートの初期設定実行
	SetDefaultRenderState();



	//test
	hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&pWriteFactory_)
		);
	//失敗時はメッセージＢＯＸを表示
	if (!SUCCEEDED(hr))
	{
		MessageBox(NULL, L"DWriteCreateFactory()に失敗", NULL, NULL);
		return ;
	}


	pWriteFactory_->CreateTextFormat(
		L"メイリオ", // フォント（ＭＳ Ｐ明朝/ＭＳ Ｐゴシックとか）
		NULL, // フォントコレクション（NULL=システムフォント）
		DWRITE_FONT_WEIGHT_NORMAL, //太さ
		DWRITE_FONT_STYLE_NORMAL, //スタイル(傾き)
		DWRITE_FONT_STRETCH_NORMAL,//幅
		100.0f,//文字の大きさ
		L"ja-jp",//ロケール(地域)/ja-jp/en-us
		&pFom
		);

	//ファクトリの作成
	D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,
		&pD2DFactory);

	//レンダーターゲットのサイズの準備
	RECT rect;
	::GetClientRect(GetHWnd(), &rect);
	D2D1_SIZE_U size =
		D2D1::Size<UINT>(rect.right, rect.bottom);

	//レンダーターゲットの作成 
	pD2DFactory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(GetHWnd(), size),
		&pHwndRenderTarget);

	pHwndRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(0.0F, 1.0F, 0.0F), &pGreenBrush);

	//dxtk
//DirectXTK
	// グローバル変数など
	//using namespace DirectX;
	//SpriteBatch* pSpriteBatch;
	//SpriteFont* pSpriteFont;

	//初期化
	//pSpriteBatch = new SpriteBatch(m_pImmediateContext);//スプライト表示
	//pSpriteFont = new SpriteFont(m_pD3DDevice, L"myfile.spritefont");//フォント表示





}

void CRenderer::Update(void)
{

}

void CRenderer::Finalize(void)
{
	if (m_pImmediateContext)
	{
		m_pImmediateContext->ClearState();
	}

	SafeRelease(m_pRenderTargetView);
	SafeRelease(m_pSwapChain);
	SafeRelease(m_pImmediateContext);
	SafeRelease(m_pD3DDevice);

	//test
	SafeRelease(pWriteFactory_);
	SafeRelease(pFom);

	//ファクトリ 
	SafeRelease(pD2DFactory);
	//レンダーターゲット 
	SafeRelease(pHwndRenderTarget);
	SafeRelease(pGreenBrush);


	
}

void CRenderer::Clear(void)
{
	//DrawText
	std::wstring wst(L"abcd文字列");

	//レイアウト
	float width = 1300.0f;
	float height = 100.0f;

	//描画位置
	D2D1_RECT_F rect;
	rect.left = 50.0f;
	rect.top = 50.0f;
	rect.right = rect.left + width;
	rect.bottom = rect.top + height;
	//pHwndRenderTarget->BeginDraw();
	//
	//pHwndRenderTarget->DrawTextW(wst.c_str(), wst.size(), pFom, rect, pGreenBrush);
	//pHwndRenderTarget->EndDraw();

	static const float ClearColor[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, ClearColor);


	

	

	//m_pRenderTargetView->Draw(wst.c_str(), wst.size(), pFom, rect,0);



	//pWriteFactory_->
	//DrawText()
	
}

void CRenderer::Present(void)
{
	m_pSwapChain->Present(0, 0);
}

void CRenderer::SetDefaultRenderState(void)
{
	ID3D11DeviceContext* m_pDevContext = m_pImmediateContext;
	ID3D11Device* pDevice = m_pD3DDevice;

	//====================================================
	// Render States
	//====================================================
	ID3D11RasterizerState* pRasterizerState = nullptr;
	D3D11_RASTERIZER_DESC  rasterizerDisc;
	ZeroMemory(&rasterizerDisc, sizeof(rasterizerDisc));
	rasterizerDisc.FillMode = D3D11_FILL_SOLID;
	rasterizerDisc.CullMode = D3D11_CULL_BACK;
	rasterizerDisc.FrontCounterClockwise = FALSE; //表面を左回りに

	HRESULT hr = pDevice->CreateRasterizerState(&rasterizerDisc, &pRasterizerState);

	//Blend States
	ID3D11BlendState* pBlendState;
	D3D11_BLEND_DESC blendDesc;
	ZeroMemory(&blendDesc, sizeof(blendDesc));

	blendDesc.RenderTarget[0].BlendEnable = TRUE;
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA; //alphablend
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_SRC_ALPHA;
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	hr = pDevice->CreateBlendState(&blendDesc, &pBlendState);

	//depth state
	ID3D11DepthStencilState* pDepthStencilState;
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	ZeroMemory(&depthStencilDesc, sizeof(depthStencilDesc));
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
	hr = pDevice->CreateDepthStencilState(&depthStencilDesc, &pDepthStencilState);

	//sampler
	ID3D11SamplerState* pSamplerState;
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(samplerDesc));
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	samplerDesc.MaxAnisotropy = 4;
	hr = pDevice->CreateSamplerState(&samplerDesc, &pSamplerState);

	//AttachState
	m_pDevContext->RSSetState(pRasterizerState);
	m_pDevContext->OMSetBlendState(pBlendState, nullptr, 0xffffffff);
	m_pDevContext->OMSetDepthStencilState(pDepthStencilState, 0);
	m_pDevContext->PSSetSamplers(0, 1, &pSamplerState);

	//Release
	SafeRelease(pRasterizerState);
	SafeRelease(pBlendState);
	SafeRelease(pDepthStencilState);
	SafeRelease(pSamplerState);
}

ID3D11Device* CRenderer::GetDevice(void)
{
	return m_pD3DDevice;
}
ID3D11DeviceContext* CRenderer::GetDeviceContext(void)
{
	return m_pImmediateContext;
}