struct VSIn
{
	float3 position				: POSITION;
	float2 texCoord				: TEXCOORD;
};

struct PSIn
{
	float4 posH					: SV_POSITION;
	float2 texCoord				: TEXCOORD;
};

PSIn VS_main(VSIn input)
{
	PSIn output;

	output.posH = float4(input.position,1);
	output.texCoord = input.texCoord;

	return output;
}
