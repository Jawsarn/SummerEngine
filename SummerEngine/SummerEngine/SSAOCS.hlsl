#define BLOCK_SIZE 16
#define SSAO_SAMPLE_AMOUNT 14

cbuffer ConstantBuffer : register(c0)
{
	matrix View;
	matrix Projection;
	float4 EyePosition;
};

cbuffer PerCompute : register(c1)
{
	float2 ScreenDimensions;
	float2 CamNearFar;

	float4 AmbientLight;
	float4 ColorOverlay;
}

cbuffer SSAOBuffer : register(c2)
{
	float4 OffsetVectors[SSAO_SAMPLE_AMOUNT];

	float OcclusionRadius;
	float OcclusionFadeStart;
	float OcclusionFadeEnd;
	float SurfaceEpsilon;
};

//input textures
Texture2D<float4> g_Normal_Depth			:register(t1);


//output texture
RWTexture2D<float> o_Output				:register(u0);

Texture1D<float4> g_RamdomMap				:register(t2);

SamplerState SamShadow : register(s0);
SamplerState SamRandom : register(s1);

struct PixelData
{
	float3 PositionView;
	float3 NormalView;
};

float3 ConstructViewFromDepth(float2 p_ScreenPos, float p_Depth)
{
	float2 screenSpaceRay = float2(p_ScreenPos.x / Projection._11, p_ScreenPos.y / Projection._22);

		return float3(float2(screenSpaceRay* p_Depth), p_Depth);
}

PixelData GetPixelData(uint2 p_GlobalCord)
{
	PixelData o_Output;

	//get depth normal data
	float t_Depth = g_Normal_Depth[p_GlobalCord].w;
	float3 t_Normal = g_Normal_Depth[p_GlobalCord].xyz;

		//
		float2 t_ScreenPixelOffset = float2(2.0f, -2.0f) / ScreenDimensions;
		float2 t_ScreenPos = (float2(p_GlobalCord)+0.5f)* t_ScreenPixelOffset + float2(-1.0f, 1.0f); //not sure if this is ok?

		t_Depth = Projection._43 / (t_Depth - Projection._33); //getting depth from projection matrix,

	o_Output.PositionView = ConstructViewFromDepth(t_ScreenPos, t_Depth);
	o_Output.NormalView = mul(float4(t_Normal, 0), View).xyz;

	return o_Output;
}

float OcclusionFunction(float distZ)
{
	float t_Occlusion = 0.0f;

	if (distZ > SurfaceEpsilon)
	{
		float t_FadeLength = OcclusionFadeEnd - OcclusionFadeStart;

		t_Occlusion = saturate((OcclusionFadeEnd - distZ) / t_FadeLength);
	}
	return t_Occlusion;
}

[numthreads(BLOCK_SIZE, BLOCK_SIZE, 1)]
void CS( uint3 p_ThreadID : SV_DispatchThreadID )
{
	
	//to gather pixel data
	uint2 t_GlobalCord = p_ThreadID.xy;

	PixelData t_Data = GetPixelData(t_GlobalCord);
	float p_Value = p_ThreadID.x*p_ThreadID.y*p_ThreadID.z;
	
	float3 t_RandomVector = 2.0f*g_RamdomMap.SampleLevel(SamRandom, p_Value*4.0f, 0).rgb - 1.0f;

	float t_OcclusionSum = 0.0f;

	[unroll]
	for (int i = 0; i < SSAO_SAMPLE_AMOUNT; i++)
	{
		float3 t_Offset = reflect(OffsetVectors[i].xyz, t_RandomVector);

		//sign returns -1 if less then zero, and 1 if more then zero, good way to see if facing same side as normal
		float t_Flip = sign(dot(t_Offset, t_Data.NormalView));

		//sample point near our position in the occlusion radius
		float3 t_SampledPoint = t_Data.PositionView + t_Flip* OcclusionRadius * t_Offset;

		//now we project the sampled point to texture space, I think this means only using the projection matrix due to its already in view space and then devide by w
		float4 t_ProjSamplePoint = mul(float4(t_SampledPoint, 1), Projection);
		t_ProjSamplePoint /= t_ProjSamplePoint.w;

		//now sample from our depth map
		float t_TestDepth = g_Normal_Depth.SampleLevel(SamShadow, t_ProjSamplePoint.xy, 0.0f).w;

		float3 t_Occluder = (t_TestDepth / t_SampledPoint.z) * t_SampledPoint;

		float distZ = t_Data.PositionView.z - t_Occluder.z;

		float distanceToPlane = max(dot(t_Data.NormalView, normalize(t_Occluder - t_Data.PositionView)), 0.0f);
		float t_Occlusion = distanceToPlane* OcclusionFunction(distZ);

		t_OcclusionSum += t_Occlusion;
	}

	float t_Amount = SSAO_SAMPLE_AMOUNT; //if not work with ints do this y
	t_OcclusionSum /= t_Amount;


	float t_Access = 1.0f - t_OcclusionSum;
	//sharpen
	o_Output[p_ThreadID.xy] = saturate(pow(t_Access, 4.0f));
}