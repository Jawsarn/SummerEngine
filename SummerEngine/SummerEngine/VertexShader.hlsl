
struct VS_INPUT
{
	float3 Position		: POSITION;
	float3 Normal		: NORMAL;
	float2 Texcord		: TEXCOORD;
	matrix World		: WORLDMATRIX;
};

struct VS_OUTPUT
{
	float4 Position		: SV_POSITION;
	float3 Normal		: NORMAL;
	float2 Texcord		: TEXCORD;
};

cbuffer ConstantBuffer : register(c0)
{
	matrix View;
	matrix Proj;
	matrix ViewProj;
};

//testar
cbuffer ConstantBuffer : register(c1)
{
	matrix world;
};


VS_OUTPUT VS(VS_INPUT p_Input)
{
	VS_OUTPUT o_Output;

	//something is wrong with view and projection so trying to render without those for now
	o_Output.Position = float4(p_Input.Position, 1);//testar

	//o_Output.Position = mul(float4(p_Input.Position, 1), p_Input.World);
	//o_Output.Position = mul(o_Output.Position, View);
	//o_Output.Position = mul(o_Output.Position, Proj);

	o_Output.Normal = p_Input.Normal;

	o_Output.Texcord = p_Input.Texcord;

	return o_Output;
}