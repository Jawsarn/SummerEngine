Texture2D fontTexture : register(t4);

SamplerState SampleType;

struct PSIn
{
	float4 posH							: SV_POSITION;
	float2 texCoord						: TEXCOORD;
};

float4 PS_main(PSIn input) : SV_TARGET
{
	//return float4(1.0f, 0.0f, 0.0f, 0.0f);
	return float4(fontTexture.Sample(SampleType, input.texCoord));
	
}
