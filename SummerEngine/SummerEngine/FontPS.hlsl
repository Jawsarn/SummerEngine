struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float3 texCoord : TEX;
};

float4 PS_main(VS_OUTPUT p_Input) : SV_TARGET
{
	return float4(1, 0, 0, 0);
}