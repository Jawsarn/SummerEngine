struct VSIn
{
	float3 position  : POSITION;
	float2 texCoord	 : TEX;
};

struct PSIn
{
	float4 position	: SV_POSITION;
	float2 texCoord : TEX;
};

PSIn VS_main(VSIn p_Input)
{
	PSIn output;

	output.position = float4(p_Input.position, 1);
	//output.texCoord = p_Input.texCoord;

	return output;
}