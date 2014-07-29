
struct VS_INPUT
{
	float3 Position		: POSITION;
	float3 Normal		: NORMAL;
	float2 TexCoord		: TEXCOORD;
	matrix World		: WORLDMATRIX;
};

struct VS_OUTPUT
{
	float4 Position		: SV_POSITION;
};

cbuffer ConstantBuffer : register(c0)
{
	matrix View;
	matrix Proj;
	float4 EyePosition;
};


VS_OUTPUT VS(VS_INPUT p_Input)
{
	VS_OUTPUT o_Output;


	o_Output.Position = mul(float4(p_Input.Position, 1), p_Input.World);
	o_Output.Position = mul(o_Output.Position, View);
	o_Output.Position = mul(o_Output.Position, Proj);

	return o_Output;
}