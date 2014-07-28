
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

PS_OUTPUT PS(PS_INPUT p_Input) : SV_TARGET
{
	PS_OUTPUT o_Output;

	float depth = p_Input.Depth.x / p_Input.Depth.y;

	o_Output.Normal_Depth = float4(p_Input.Normal, depth);
	o_Output.DiffuseColor_Spec = float4(p_Input.Texcord, 1, 1);
	o_Output.Temp = float4(1, 1, 1, 1);

	return o_Output;
}