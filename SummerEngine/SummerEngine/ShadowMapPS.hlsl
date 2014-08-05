
struct PS_INPUT
{
	float4 Position : SV_POSITION;
	float2 Depth		: DEPTH;
};


float PS(PS_INPUT p_Input) : SV_TARGET
{
	float depth = p_Input.Depth.x / p_Input.Depth.y;
	return depth;
}