
struct VS_OUTPUT
{
	float4 Pos			: SV_POSITION;
	float2 TexCoord		: TEXCOORD;
};

float4 PS(VS_OUTPUT p_Input) : SV_TARGET
{
	//return float4(1.0f, 1.0f, 1.0f, 1.0f);

	//return float4(p_Input.TexCoord, 0, 1);
	float4 diffuse = float4(0.5f, 0.0f, 0.0f, 1);
	return diffuse;
}