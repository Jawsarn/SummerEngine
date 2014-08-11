struct VSIn
{
	float3 Pos				: POSITION;
	float2 TexCoord		    : TEXCOORD;
	float3 Color		  	: COLOR;
};

struct PSIn
{
	float4 Pos			: SV_POSITION;
	float2 TexCoord		: TEXCOORD;
	float3 Color		: COLOR;
};

cbuffer WORLD : register (b0)
{
	matrix world;
}

PSIn VS(VSIn p_Input)
{
	PSIn output;

	output.Pos = float4(p_Input.Pos, 1);
	//output.Pos = mul(output.Pos, world);
	output.TexCoord = p_Input.TexCoord;
	output.Color = p_Input.Color;

	return output;
}