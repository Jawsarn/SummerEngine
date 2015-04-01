

//Material packed by 4 floats
cbuffer Material	: register(c0)
{
	float Ns;					//Shininess of the material
	float3 Ka;				//Ambient color (r,g,b)
	
	float Ni;					//Reflection index
	float3 Kd;				//Diffuse color (r,g,b)

	float D;					//Transparency Tr (alpha)
	float3 Ks;				//Specular color (r,g,b)
	
	float3 Tf;				//Color Transperancy color (d or Tr)
	float Ke;					//Emissive color

	uint Illum;				//Define the illumination model: illum = 1 a flat material with no specular highlights, illum = 2 denotes the presence of specular highlights
	uint3 filler;
};

//textures from material
Texture2D m_Map_Kd		: register(t0);		//diffuse
Texture2D m_Map_Ka		: register(t1);		//ambient
Texture2D m_Map_Ks		: register(t2);		//specular
Texture2D m_Map_Ke		: register(t3);		//emissive fucked up shit
Texture2D m_Map_Ns		: register(t4);		//specular shinyness
Texture2D m_Map_D		: register(t5);		//transparency
Texture2D m_Bump		: register(t6);		//normal map
Texture2D m_Disp		: register(t7);		//displacment map
Texture2D m_Occulsion	: register(t8);		//diffuse blackmap



struct PS_INPUT
{
	float4 Position		: SV_POSITION;
	float3 Normal		: NORMAL;
	float3 Tangent		: TANGENT;
	float2 TexCoord		: TEXCOORD;
	float2 Depth		: DEPTH;
};

struct PS_OUTPUT
{
	float4 Normal_Depth			:SV_TARGET0;
	float4 Diffuse_Spec			:SV_TARGET1;
	float4 Temp					:SV_TARGET2;
};

PS_OUTPUT PS(PS_INPUT p_Input)
{
	PS_OUTPUT o_Output;

	float t_Depth = p_Input.Depth.x / p_Input.Depth.y;

	//add calculation to offset normalmap from the current normals
	float3 t_Normal = p_Input.Normal;

	o_Output.Normal_Depth = float4(t_Normal, t_Depth);

	float3 t_Diffuse = float3(0, 1, 1);
	float t_Specular = 1;

	o_Output.Diffuse_Spec = float4(t_Diffuse, t_Specular);

	o_Output.Temp = float4(0, 1, 0, 0);

	return o_Output;
}