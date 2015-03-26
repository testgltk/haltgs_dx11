struct vertexIn
{
	float3 pos : POSITION;
	float4 col : COLOR;
	float2 tex : TEXCOORD;
};

struct vertexOut
{
	float4 pos : SV_POSITION;
	float4 col : COLOR;
	float2 tex : TEXCOORD;
};

cbuffer ConstantBuffer : register (b0)
{
	matrix worldViewProjection;
}

Texture2D DiffuseMap : register (t0);

SamplerState samAnisotropic: register (s0)
{
	Filter = ANISOTROPIC;
	//Filter = MIN_MAG_MIP_LINEAR;
	maxAnisotropy = 4;
	AddressU = WRAP;
	AddressV = WRAP;
	AddressW = WRAP;
	ComparisonFunc = NEVER;
	MinLOD = 0;
	MaxLOD = FLOAT32_MAX;
};

vertexOut  VertexShaderPolygon(vertexIn IN)
{
	vertexOut OUT;
	OUT.pos = mul(float4(IN.pos,1.0f), worldViewProjection);
	OUT.tex = IN.tex;
	OUT.col = IN.col;
	return OUT;
}

float4 PixelShaderPolygon(vertexOut IN) : SV_TARGET
{
	return DiffuseMap.Sample(samAnisotropic, IN.tex)* IN.col;
}

vertexOut  main(vertexIn IN)
{
	vertexOut OUT;
	OUT.pos = mul(IN.pos, worldViewProjection);
	OUT.col = IN.col;
	OUT.tex = IN.tex;
	return OUT;
}

/*
technique StartShader
{
	pass P0
	{
		//SetVertexShader(CompileShader(vs_4_0, VertexShaderPolygon()));
		SetVertexShader(NULL);
		SetGeometryShader(NULL);
		//SetPixelShader(CompileShader(vs_4_0, PixelShaderPolygon()));
		SetPixelShader(NULL);
	}
};
*/