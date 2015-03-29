
//todo: make this macro so we can adjust it from outside
#define BLOCK_SIZE 16



//output texture (share same register as resource views)
RWTexture2D<float4> o_Output				:register(u0);

//input textures
Texture2D<float4> m_Normal_Depth			:register(t1);
Texture2D<float4> m_DiffuseColor_Spec		:register(t2);
Texture2D<float4> m_Specular				:register(t3);

//sampler



[numthreads(BLOCK_SIZE, BLOCK_SIZE, 1)]
void CS( uint3 p_ThreadID : SV_DispatchThreadID )
{
	//if within screen
	if (0 <= p_ThreadID.x < 1920 && 0 <= p_ThreadID.y < 1080)
	{
		o_Output[p_ThreadID.xy] = float4(m_Normal_Depth[p_ThreadID.xy].xyz, 0);
	}
}