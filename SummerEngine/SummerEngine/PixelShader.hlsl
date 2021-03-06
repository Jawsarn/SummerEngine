
struct VS_OUTPUT
{
	float4 Position		: SV_POSITION;
	float3 Normal		: NORMAL;
	float2 TexCoord		: TEXCORD;
};

float4 PS(VS_OUTPUT p_Input) : SV_TARGET
{
	//return float4(1.0f, 1.0f, 1.0f, 1.0f);
	return float4(p_Input.TexCoord, 0, 1);
}