#define BLOCK_SIZE 16

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

cbuffer ShadowMapBuffer : register(c2)
{
	matrix ShadowMatrix;
	float Shadow_Width;
	float Shadow_Height;
	float2 fillers;
};

struct PointLight
{
	float3 position;
	float radius;

	float3 color;
	float filler;
};

struct SpotLight
{
	float3 position;
	float radius;

	float3 color;
	float filler;

	float3 direction;
	float filler2;
};


//input textures
Texture2D<float4> g_Normal_Depth			:register(t1);
Texture2D<float4> g_DiffuseColor_Spec		:register(t2);
Texture2D<float4> g_Specular				:register(t3);

//output texture
RWTexture2D<float4> o_Output				:register(u0);

//lights
StructuredBuffer<PointLight> g_PointLights	:register(t4);
Texture2D<float> g_ShadowMap				:register(t5);

//groupshared
groupshared uint g_MinDepth;
groupshared uint g_MaxDepth;
groupshared uint g_VisibleLightCount;
groupshared uint g_VisibleLightIndices[1024];

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
	float2 t_ScreenPos = (float2(p_GlobalCord) + 0.5f)* t_ScreenPixelOffset + float2(-1.0f, 1.0f); //not sure if this is ok?

	t_Depth = Projection._43 / (t_Depth - Projection._33); //getting depth from projection matrix,

	o_Output.PositionView = ConstructViewFromDepth(t_ScreenPos, t_Depth);
	o_Output.NormalView = mul(float4(t_Normal, 0), View).xyz;

	return o_Output;
}

void CalculateDepth(uint p_GroupIndex, PixelData p_Data)
{
	//setting Max to min distance, and Min to max distance for checking
	float t_TestMinZ = CamNearFar.y;
	float t_TestMaxZ = CamNearFar.x;

	float t_Depth = p_Data.PositionView.z;

	bool t_ValidPixel = t_Depth >= CamNearFar.x && t_Depth < CamNearFar.y; //to check if the pixel is inside the camera range, if nothing is drawn depth is 0, => a large box is something else is far away
	if (t_ValidPixel)
	{
		t_TestMinZ = min(t_TestMinZ, t_Depth);
		t_TestMaxZ = max(t_TestMaxZ, t_Depth);
	}

	if (p_GroupIndex == 0) //initialize variables
	{
		g_MinDepth = 0x7F7FFFFF;
		g_MaxDepth = 0;
		g_VisibleLightCount = 0;
	}

	GroupMemoryBarrierWithGroupSync();

	if (t_TestMaxZ >= t_TestMinZ) //to check if it is a valid data
	{
		InterlockedMax(g_MaxDepth, asuint(t_TestMaxZ));
		InterlockedMin(g_MinDepth, asuint(t_TestMinZ));
	}

	GroupMemoryBarrierWithGroupSync();
}

void CalculateFrustrums(uint2 p_GroupID, inout float4 p_FrustrumPlanes[6] )
{
	float t_MinTileY = asfloat(g_MinDepth); 
	float t_MaxTileY = asfloat(g_MaxDepth); 

	float2 t_TileScale = float2(ScreenDimensions * rcp(float(2 * BLOCK_SIZE)));
	float2 t_TileBias = t_TileScale - float2(p_GroupID);

	float4 c1 = float4(Projection._11 * t_TileScale.x,		 0.0f,								t_TileBias.x,			0.0f);
	float4 c2 = float4(0.0f,								-Projection._22*t_TileScale.y,		t_TileBias.y,			0.0f);
	float4 c4 = float4( 0.0f,								0.0f,								1.0f,					0.0f);

	p_FrustrumPlanes[0] = c4 - c1;
	p_FrustrumPlanes[1] = c4 + c1;
	p_FrustrumPlanes[2] = c4 - c2;
	p_FrustrumPlanes[3] = c4 + c2;

	p_FrustrumPlanes[4] = float4(0.0f, 0.0f, 1.0f, -t_MinTileY);
	p_FrustrumPlanes[5] = float4(0.0f, 0.0f, 1.0f, t_MaxTileY);

	for (int i = 0; i < 4; i++) //normalize the planes
	{
		p_FrustrumPlanes[i] *= rcp(length(p_FrustrumPlanes[i].xyz));
	}
}

float3 DirectIllumination(float3 pos, float3 norm, PointLight light, float inSpec)
{
	float3 lightPos = mul(float4(light.position, 1), View).xyz;

	float3 lightVec = lightPos - pos;

	float d = length(lightVec);
	if (d > light.radius)
	{
		return float3(0, 0, 0);
	}

	lightVec /= d;
	float diffuseFactor = dot(lightVec, norm);

	if (diffuseFactor < 0.0f)
	{
		return float3(0, 0, 0);
	}

	float att = pow(max(0.0f, 1.0 - (d / light.radius)), 2.0f);

	float3 toEye = normalize(-pos);
		float3 v = reflect(-lightVec, norm);


	float specFactor = pow(max(dot(v, toEye), 0.0f), 1.0f)*inSpec;

	return (light.color *att * (diffuseFactor + specFactor));
}

void CalculateTileAndLightCollision(uint p_MaxNumOfPointLights, uint p_GroupIndex, float4 p_FrustrumPlanes[6])
{
	uint t_GroupSize = BLOCK_SIZE * BLOCK_SIZE;

	//lightcull for this tile, may change more towards the dice implementation maxNumOfLights
	for (uint lightIndex = p_GroupIndex; lightIndex < p_MaxNumOfPointLights; lightIndex += t_GroupSize)
	{
		PointLight light = g_PointLights[lightIndex];


		bool inFrustum = true;
		for (int i = 0; i < 6 && inFrustum; i++) //6
		{
			float4 lightPos = mul(float4(light.position, 1), View);

				float distance = dot(p_FrustrumPlanes[i], lightPos);
			inFrustum = inFrustum && (distance >= -light.radius);
		}
		if (inFrustum)
		{
			uint index;
			InterlockedAdd(g_VisibleLightCount, 1, index); //outputs pre number to index
			g_VisibleLightIndices[index] = lightIndex;
		}
	}

	GroupMemoryBarrierWithGroupSync();
}



float3 CalculateLighting(uint2 p_ThreadID, PixelData p_Data)
{
	uint numOfLights = g_VisibleLightCount;


	float3 matColor = g_DiffuseColor_Spec[p_ThreadID].xyz;
	float3 finalColor = matColor*AmbientLight.xyz + ColorOverlay.xyz;

	float inSpec = g_DiffuseColor_Spec[p_ThreadID].w;

	//if(all(globalCord < screenDimensions)) //checks for all components if blow zero, uses this for checking if outside screendim
	//{
	for (uint i = 0; i < g_VisibleLightCount; i++)
	{
		uint lightIndex = g_VisibleLightIndices[i];
		PointLight light = g_PointLights[lightIndex];

		finalColor += matColor*DirectIllumination(p_Data.PositionView, p_Data.NormalView, light, inSpec);
	}
	//}


	if ((p_Data.NormalView.x + p_Data.NormalView.y + p_Data.NormalView.z) == 0)
	{
		finalColor = g_DiffuseColor_Spec[p_ThreadID].xyz;
	}

	return finalColor;
}

float CalcShadowFactor(PixelData p_Data)
{
	float4 t_ShadowPos = mul(float4(p_Data.PositionView, 1), ShadowMatrix);
		t_ShadowPos.xyz /= t_ShadowPos.w;

	float t_Depth = t_ShadowPos.z;

	if (t_ShadowPos.x >= 0.0f && t_ShadowPos.x <= 1.0f && 
		t_ShadowPos.y >= 0.0f && t_ShadowPos.y <= 1.0f)
	{
		uint x = asuint(t_ShadowPos.x);
		uint y = asuint(t_ShadowPos.y);
		uint2 cordinates = uint2( x* Shadow_Width,  y* Shadow_Height);
		
		float t_ShadowDepth = g_ShadowMap[cordinates];
		if (t_ShadowDepth < t_Depth)
		{
			return 0.0f;
		}
		else
		{
			return 1.0f;
		}
	}
	else
	{
		return 1.0f;
	}
}

[numthreads(BLOCK_SIZE, BLOCK_SIZE, 1)]
void CS( uint3 p_ThreadID : SV_DispatchThreadID, uint3 p_GroupThreadID : SV_GroupThreadID, uint3 p_GroupID : SV_GroupID )
{
	//to gather pixel data
	uint2 t_GlobalCord = p_ThreadID.xy;

	//get number of Lights
	uint t_MaxNumOfLights, stride;
	g_PointLights.GetDimensions(t_MaxNumOfLights, stride);

	//index 0 initialize variables
	uint t_GroupIndex = p_GroupThreadID.x + p_GroupThreadID.y * BLOCK_SIZE;

	//get pixel data
	PixelData t_Data = GetPixelData(t_GlobalCord);
	
	//calculate the tile group depth with interlocked method and barrier
	CalculateDepth(t_GroupIndex, t_Data);

	//calculate the frustrums to cover the gathered depth values
	float4 t_FrustrumPlanes[6]; //a box, 6 of em
	CalculateFrustrums(p_GroupID, t_FrustrumPlanes);

	CalculateTileAndLightCollision(t_MaxNumOfLights, t_GroupIndex, t_FrustrumPlanes);

	float3 finalColor = CalculateLighting(p_ThreadID.xy, t_Data);

	float t_DepthFactor = CalcShadowFactor(t_Data);

	finalColor *= t_DepthFactor;

	//o_Output[p_ThreadID.xy] = g_DiffuseColor_Spec[p_ThreadID.xy];
	o_Output[p_ThreadID.xy] = float4(finalColor, 1);
	//o_Output[p_ThreadID.xy] = g_Normal_Depth[p_ThreadID.xy];
	//o_Output[p_ThreadID.xy] = float4(g_MaxDepth, g_MaxDepth, g_MaxDepth, 1);
	//o_Output[p_ThreadID.xy] = float4(t_Data.NormalView.x, t_Data.NormalView.y, t_Data.NormalView.z, 0);
	/*float deepth = g_ShadowMap[p_ThreadID.xy];
	o_Output[p_ThreadID.xy] = float4(deepth, deepth, deepth,1);*/
}