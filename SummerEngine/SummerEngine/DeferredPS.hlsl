
struct PS_INPUT
{
	float4 Position : SV_POSITION;
	float3 Normal	: NORMAL;
	float2 Texcord	: TEXCOORD;
	float2 Depth	: DEPTH;
};

struct PS_OUTPUT
{
	float4 Normal_Depth			:SV_TARGET0;
	float4 DiffuseColor_Spec	:SV_TARGET1;
	float4 Temp					:SV_TARGET2;
};

SamplerState g_Sampler		: register(s0);

Texture2D g_DiffuseTexture	: register(t0);
Texture2D g_NormalTexture	: register(t1);

PS_OUTPUT PS(PS_INPUT p_Input) : SV_TARGET
{
	PS_OUTPUT o_Output;

	float depth = p_Input.Depth.x / p_Input.Depth.y;

	float4 NormalColor = g_DiffuseTexture.Sample(g_Sampler, p_Input.Texcord);
	o_Output.Normal_Depth = float4(p_Input.Normal, depth);

	float4 DiffuseColor = g_DiffuseTexture.Sample(g_Sampler, p_Input.Texcord);
	o_Output.DiffuseColor_Spec = float4(DiffuseColor.xyz, 1.0f);
	o_Output.Temp = float4(1, 1, 1, 1);

	return o_Output;
}