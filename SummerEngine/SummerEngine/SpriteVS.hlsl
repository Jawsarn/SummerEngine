struct VSIn
{
	float3 Pos				 : POSITION;
	float2 TexCoord			 : TEXCOORD;
};

struct PSIn
{
	float4 Pos : SV_POSITION;
	float3 WorldPos : POSITION;
	float2 TexCoord : TEX;
};

PSIn VS(VSIn p_Input)
{
	PSIn output;

	output.Pos = float4(p_Input.Pos, 1);
	output.TexCoord = p_Input.TexCoord;

	return output;
}