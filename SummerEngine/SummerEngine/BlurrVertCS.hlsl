

cbuffer cbSettings
{
	static const float g_Weights[11] =
	{
		/*0.00f, 0.00f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.00f, 0.00f,*/
		0.05f, 0.05f, 0.1f, 0.1f, 0.1f, 0.2f, 0.1f, 0.1f, 0.1f, 0.05f, 0.05f,
		/*0.08f, 0.08f, 0.15f, 0.15f, 0.25f, 0.3f, 0.25f, 0.15f, 0.15f, 0.08f, 0.08f,*/
		/*0.02f, 0.02f, 0.02f, 0.04f, 0.05f, 0.05f, 0.1f, 0.1f, 0.2f, 0.1f, 0.1f, 0.05f, 0.05f, 0.04f, 0.02f, 0.02f, 0.02f,*/
	};
}

cbuffer cbFixed
{
	static const int g_BlurRadius = 5;
}

RWTexture2D<float> g_Output : register(u0);
Texture2D<float> g_Input : register(t1);
Texture2D<float4> g_Normal_Depth : register(t2);

SamplerState SamShadow : register(s2);
SamplerState SamRandom : register(s1);
SamplerState SamNormal : register(s0);

#define N 256
#define CacheSize (N + 2*g_BlurRadius)

groupshared float g_Cache[CacheSize];

[numthreads(1, N, 1)]
void CS(int3 groupThreadID : SV_GroupThreadID, int3 threadID : SV_DispatchThreadID)
{
	float2 uvDimensions = float2(1.0f / 1920.0f, 1.0f / 1080.0f);

	if (groupThreadID.y < g_BlurRadius)
	{
		// Clamp out of bound samples that occur at image borders.
		int y = max(threadID.y - g_BlurRadius, 0);
		g_Cache[groupThreadID.y] = g_Input.SampleLevel(SamNormal, float2(threadID.x*uvDimensions.x, y*uvDimensions.y), 0);
	}

	if (groupThreadID.y >= N - g_BlurRadius)
	{
		// Clamp out of bound samples that occur at image borders.
		int y = min(threadID.y + g_BlurRadius, g_Input.Length.y - 1);

		g_Cache[groupThreadID.y + 2 * g_BlurRadius] = g_Input.SampleLevel(SamNormal, float2(threadID.x*uvDimensions.x, y*uvDimensions.y), 0);
	}

	// Clamp out of bound samples that occur at image borders.
	g_Cache[groupThreadID.y + g_BlurRadius] = g_Input.SampleLevel(SamNormal, uvDimensions*min(threadID.xy, g_Input.Length.xy - 1), 0);

	// Wait for all threads to finish.
	GroupMemoryBarrierWithGroupSync();

	//
	// Now blur each pixel.
	//
	float blurColor = 0.0f;
	float t_TotalWeight = 0.0f;
	float4 t_Normal_Depth = g_Normal_Depth.SampleLevel(SamNormal, threadID.xy / float2(1920, 1080), 0.0f);


	[unroll]
	for (int i = -g_BlurRadius; i <= g_BlurRadius; ++i)
	{

		float2 texCords = ((threadID.xy + uint2(0, i)) / float2(1920.0f, 1080.0f));

		float4 t_Test_Normal_Depth = g_Normal_Depth.SampleLevel(SamNormal, texCords, 0.0f);

		
		if (dot(t_Test_Normal_Depth.xyz, t_Normal_Depth.xyz) >= 0.8f &&
			abs(t_Test_Normal_Depth.w - t_Normal_Depth.w) <= 0.2f)
		{
			int k = groupThreadID.y + g_BlurRadius + i;
			blurColor += g_Weights[i + g_BlurRadius] * g_Cache[k];
			t_TotalWeight += g_Weights[i + g_BlurRadius];
		}
	}

	g_Output[threadID.xy] = blurColor / t_TotalWeight;

}