//==============================================================================
// File		Sprite.cpp
// Comment	2Dポリゴン表示クラス
// Author	TOMOHIRO KOUNO
// Create	2014年12月31日
//==============================================================================

//------------------------------------------------------------------------------
// インクルード
//------------------------------------------------------------------------------
#include "Sprite.h"
#include "System/SystemManager.h"

ID3D11VertexShader*	CSprite::m_pVertexShader   = nullptr;
ID3D11PixelShader*	CSprite::m_pPixelShader    = nullptr;
ID3D11InputLayout*	CSprite::m_pVertexLayout   = nullptr;
ID3D11Buffer*		CSprite::m_pConstantBuffer = nullptr;

CSprite::CSprite(const PARAM& param)
:m_Position(param.m_Position)
, m_Rotation(param.m_Rotation)
,m_TextureName(param.m_TextureName)
{
	HRESULT hr	= CreateShader();
	hr			= CreatePolygon();
}

CSprite::CSprite(void)
	:m_Position(XMFLOAT2(0,0))
	, m_Rotation(0.0f)
	, m_TextureName(L"")
{
	HRESULT hr = CreateShader();
	hr = CreatePolygon();
}

CSprite::~CSprite(void)
{
	SafeRelease(m_pVertexBuffer);
	SafeRelease(m_pVertexLayout);
	SafeRelease(m_pPixelShader);
	SafeRelease(m_pVertexShader);
	SafeRelease(m_pConstantBuffer);
	SafeRelease(m_pShaderResView);
}

void CSprite::Finalize(void)
{

}

void CSprite::Update(void)
{

}

void CSprite::Draw(void)
{
	using namespace ns_ConstantTable;

	// 頂点バッファ設定
	UINT stride = sizeof(Vertex3D);
	UINT offset = 0;

	ID3D11DeviceContext* m_pDevContext = GETDEVICECONTEXT;
	ID3D11Device* pDevice = GETDEVICE;

	m_pDevContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	m_pDevContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	m_pDevContext->IASetInputLayout(m_pVertexLayout);
	m_pDevContext->PSSetShader(m_pPixelShader, NULL, 0);
	m_pDevContext->VSSetShader(m_pVertexShader, NULL, 0);
	m_pDevContext->PSSetShaderResources(0, 1, &m_pShaderResView);

	// マトリクス設定
	XMMATRIX world, view, projection, worldViewProjection;

	//カメラ設定
	world = XMMatrixIdentity();
	world = XMMatrixRotationRollPitchYaw(0.0f, 0.0f, m_Rotation);
	world *= XMMatrixTranslation(m_Position.x, m_Position.y, 0.0f);

	//3D Transform
	//view = XMMatrixLookAtLH(XMVectorSet(0.0f, 9.0f, -55.0f, 1.0f),
	//XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f),
	//XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f));
	//projection = XMMatrixPerspectiveFovLH(1.0f, (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.0f, 100.0f);
	//worldViewProjection = world * view * projection;

	//2D Transform
	view = XMMatrixIdentity();
	projection = XMMATRIX((float)(2 / (float)SCREEN_WIDTH), 0.0f, 0.0f, 0.0f,
						 0.0f,				(float)(-2 / (float)SCREEN_HEIGHT),	0.0f, 0.0f,
						 0.0f,				0.0f,				1.0f, 0.0f,
						-1.0f,				1.0f,				0.0f, 1.0f);
	worldViewProjection = world * view * projection;

	ConstantBuffer cb;
	cb.WorldViewProjection = XMMatrixTranspose(worldViewProjection);
	m_pDevContext->UpdateSubresource(m_pConstantBuffer, 0, NULL, &cb, 0, 0);
	m_pDevContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	// ポリゴン描画
	m_pDevContext->Draw(4, 0);
}

HRESULT CSprite::CreateShader(void)
{
	HRESULT hr;
	// 頂点シェーダコンパイル・生成
	ID3DBlob* pErrorBlob;
	ID3DBlob* pVSBlob = NULL;

	//Device
	ID3D11Device* pDevice = nullptr;
	pDevice = GETDEVICE;

	//全スプライトで一度だけ頂点シェーダを生成
	if (!m_pVertexShader)
	{
		FILECHECK(L"Resources/SHADER/shader.hlsl");

		hr = D3DX11CompileFromFile(L"Resources/SHADER/shader.hlsl", NULL, NULL, "VertexShaderPolygon", "vs_4_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, NULL, &pVSBlob, &pErrorBlob, NULL);
		if (FAILED(hr))
		{
			MessageBox(NULL, (LPCWSTR)pErrorBlob->GetBufferPointer(), L"VS", MB_OK | MB_ICONERROR);
		}
		pDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &m_pVertexShader);
	}

	//全スプライトで一度だけ頂点レイアウトを生成
	if (!m_pVertexLayout)
	{
		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,	0,  0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR"	, 0, DXGI_FORMAT_R32G32B32A32_FLOAT,0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,		0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};
		UINT numElements = ARRAYSIZE(layout);

		pDevice->CreateInputLayout(layout,
			numElements,
			pVSBlob->GetBufferPointer(),
			pVSBlob->GetBufferSize(),
			&m_pVertexLayout);
			SafeRelease(pVSBlob);
	}
	
	//全スプライトで一度だけピクセルシェーダを生成
	if (!m_pPixelShader)
	{
		ID3DBlob* pPSBlob = NULL;
		FILECHECK(L"Resources/SHADER/shader.hlsl");
		hr = D3DX11CompileFromFile(L"Resources/SHADER/shader.hlsl", NULL, NULL, "PixelShaderPolygon", "ps_4_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, NULL, &pPSBlob, &pErrorBlob, NULL);
		if (FAILED(hr))
		{
			MessageBox(NULL, (LPCWSTR)pErrorBlob->GetBufferPointer(), L"PS", MB_OK | MB_ICONERROR);
		}

		pDevice->CreatePixelShader(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), NULL, &m_pPixelShader);

		SafeRelease(pPSBlob);
	}

	// 定数バッファ生成
	if (!m_pConstantBuffer)
	{
		D3D11_BUFFER_DESC hBufferDesc;
		hBufferDesc.ByteWidth			= sizeof(ConstantBuffer);
		hBufferDesc.Usage				= D3D11_USAGE_DEFAULT;
		hBufferDesc.BindFlags			= D3D11_BIND_CONSTANT_BUFFER;
		hBufferDesc.CPUAccessFlags		= 0;
		hBufferDesc.MiscFlags			= 0;
		hBufferDesc.StructureByteStride = sizeof(float);

		if (FAILED(pDevice->CreateBuffer(&hBufferDesc, NULL, &m_pConstantBuffer)))
		{
			MSGBOX(L"Create ConstantBuffer ERROR");
		}
	}

	return hr;
}

HRESULT CSprite::CreatePolygon(void)
{
	HRESULT hr = S_OK;


	// 頂点バッファ生成
	Vertex3D *vertex = new Vertex3D[4];

	vertex[0].Position	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[0].Color		= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[0].TexCoord	= XMFLOAT2(0.0f, 0.0f);

	vertex[1].Position	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[1].Color		= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[1].TexCoord	= XMFLOAT2(1.0f, 0.0f);

	vertex[2].Position	= XMFLOAT3(0.0f, 0.0f,  0.0f);
	vertex[2].Color		= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[2].TexCoord	= XMFLOAT2(0.0f, 1.0f);

	vertex[3].Position	= XMFLOAT3(0.0f, 0.0f, 0.0f);
	vertex[3].Color		= XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	vertex[3].TexCoord	= XMFLOAT2(1.0f, 1.0f);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	//bd.Usage = D3D11_USAGE_DEFAULT;
	bd.Usage = D3D11_USAGE_DYNAMIC;

	bd.ByteWidth = sizeof(Vertex3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	//bd.CPUAccessFlags = 0;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	ID3D11Device* pDevice = nullptr;
	pDevice = GETDEVICE;

	if (m_TextureName != L"" && FILECHECK(m_TextureName))
	{
		// テクスチャ生成
		D3DX11CreateShaderResourceViewFromFile(pDevice,
			m_TextureName.c_str(),
			NULL,
			NULL,
			&m_pShaderResView,
			NULL);

		//GetTextureInfo
		ID3D11Resource* pResource = nullptr;
		m_pShaderResView->GetResource(&pResource);
		ID3D11Texture2D* pTexture = static_cast<ID3D11Texture2D*>(pResource);
		D3D11_TEXTURE2D_DESC texture2D_Desc;
		ZeroMemory(&texture2D_Desc, sizeof(texture2D_Desc));
		pTexture->GetDesc(&texture2D_Desc);

		//polygonsize init is TextureSize

		m_Width = texture2D_Desc.Width;
		m_Height = texture2D_Desc.Height;

		SafeRelease(pResource);
		SafeRelease(pTexture);
	}
	else
	{
		m_Width = 32.0f;
		m_Height = 32.0f;
	}

	
	hr = pDevice->CreateBuffer(&bd, &sd, &m_pVertexBuffer);

	//Polygon Size Diffinition
	SetPolygonAlign(m_Align);
	delete[] vertex;

	return hr;
}

void CSprite::SetPosition(const XMFLOAT2& pos)
{
	m_Position = pos;
}

void CSprite::SetRotation(float Rotation)
{
	m_Rotation = Rotation;
}

void CSprite::SetPolygonAlign(CSprite::ALIGN align)
{
	ID3D11DeviceContext* m_pDevContext = GETDEVICECONTEXT;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	m_pDevContext->Map(m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	Vertex3D* pVertex = (Vertex3D*)mappedResource.pData;
	
	if (align == ALIGN_LEFT_TOP)
	{
		pVertex[0].Position = XMFLOAT3(	  0.0f,     0.0f, 0.0f);
		pVertex[1].Position = XMFLOAT3(m_Width,     0.0f, 0.0f);
		pVertex[2].Position = XMFLOAT3(   0.0f, m_Height, 0.0f);
		pVertex[3].Position = XMFLOAT3(m_Width, m_Height, 0.0f);
	}
	else if (align == ALIGN_CENTER)
	{
		float Half_W = m_Width * 0.5f;
		float Half_H = m_Height* 0.5f;
		pVertex[0].Position = XMFLOAT3(-Half_W, -Half_H, 0.0f);
		pVertex[1].Position = XMFLOAT3( Half_W, -Half_H, 0.0f);
		pVertex[2].Position = XMFLOAT3(-Half_W,  Half_H, 0.0f);
		pVertex[3].Position = XMFLOAT3( Half_W,  Half_H, 0.0f);
	}
	m_pDevContext->Unmap(m_pVertexBuffer, 0);
}

void CSprite::SetWidth(float Width)
{
	m_Width = Width;
	SetPolygonAlign(m_Align);
}

void CSprite::SetHeight(float Height)
{
	m_Height = Height;
	SetPolygonAlign(m_Align);
}

void CSprite::SetColor(const XMFLOAT4& color)
{
	ID3D11DeviceContext* m_pDevContext = GETDEVICECONTEXT;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	m_pDevContext->Map(m_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	Vertex3D* pVertex = (Vertex3D*)mappedResource.pData;
	pVertex[0].Color = 
	pVertex[1].Color = 
	pVertex[2].Color = 
	pVertex[3].Color = color;
	m_pDevContext->Unmap(m_pVertexBuffer, 0);
}

void CSprite::SetTexture(ID3D11ShaderResourceView* pTextureResource)
{
	//テクスチャがファクトリメソッドでない場合は
	//毎回以前のテクスチャを解放しておく
	SafeRelease(m_pShaderResView);
	m_pShaderResView = pTextureResource;
}

void CSprite::SetTextureUnsafeFont(ID3D11ShaderResourceView* pTextureResource)
{
	m_pShaderResView = pTextureResource;
}

void CSprite::SetTextureNone(void)
{
	//重複テクスチャ参照を回避するためのものここでは解放をしない
	m_pShaderResView = nullptr;
}

XMFLOAT2 CSprite::GetPosition(void)
{
	return m_Position;
}

float CSprite::GetWidth(void)
{
	return m_Width;
}

float CSprite::GetHeight(void)
{
	return m_Height;
}