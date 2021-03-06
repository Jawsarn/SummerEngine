//Texture2D spriteTexture : register (t10);
//SamplerState SampleType;

cbuffer SpriteColor : register(b3)
{
	float3 m_Color;
};

struct VS_OUTPUT
{
	float4 Pos			: SV_POSITION;
	float2 TexCoord		: TEXCOORD;
	float3 Color		: COLOR;
};

float4 PS(VS_OUTPUT p_Input) : SV_TARGET
{
	//return float4(1.0f, 1.0f, 1.0f, 1.0f);


	//float4 t_Color = float4(m_Color, 1);

	//return float4(p_Input.TexCoord, 0, 1);
	//return spriteTexture.Sample(SampleType, p_Input.TexCoord);

	float4 t_Color = float4(p_Input.Color,1);

	return t_Color;
}