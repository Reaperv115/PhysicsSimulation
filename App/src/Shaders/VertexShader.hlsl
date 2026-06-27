#pragma pack_matrix(row_major)

struct VS_INPUT
{
	float3 Pos : POSITION0;
    float4 Color : COLOR0;
};
struct VS_OUTPUT
{
	float4 Pos : SV_POSITION;
	float4 Color : COLOR0;
};

cbuffer MatrixBuffer : register(b0)
{
    matrix wvpMat;
};

VS_OUTPUT main(VS_INPUT input)
{
    VS_OUTPUT output;
    output.Pos = mul(float4(input.Pos, 1.0f), wvpMat);
    output.Color = input.Color;
    return output;
	
}