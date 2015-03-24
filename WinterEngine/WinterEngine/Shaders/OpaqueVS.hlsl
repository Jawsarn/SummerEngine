


cbuffer PerFrameCBuffer	: register(c0)
{
	matrix View;
	matrix Proj;
	matrix ViewProj;
	float4 EyePosition;
};


struct VS_INPUT
{
	float3 Position		: POSITION;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord		: TEXCOORD;
	matrix World		: WORLDMATRIX;
};

struct VS_OUTPUT
{
	float4 Position		: SV_POSITION;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord		: TEXCOORD;
	float2 Depth		: DEPTH;
};

VS_OUTPUT VS(VS_INPUT p_Input)
{
	VS_OUTPUT o_Output;

	//transform positions, through instanced world matrix, and then viewproj
	o_Output.Position = mul(float4(p_Input.Position, 1), p_Input.World);
	o_Output.Position = mul(o_Output.Position, ViewProj);

	//transform normal to world
	o_Output.Normal = mul(float4(p_Input.Normal, 0), p_Input.World).xyz;

	//transform tangent to world
	o_Output.Tangent = mul(float4(p_Input.Tangent, 0), p_Input.World).xyz;

	//set texcord n' depth
	o_Output.TexCoord = p_Input.TexCoord;
	o_Output.Depth = o_Output.Position.zw;


	return o_Output;
}