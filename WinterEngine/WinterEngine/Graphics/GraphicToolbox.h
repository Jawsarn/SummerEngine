#pragma once
#include <string>

namespace SGEngine
{
	typedef unsigned int MeshHandle;
	typedef unsigned int MaterialHandle;
	//typedef unsigned int UINT;

	struct RenderObject
	{
		MeshHandle meshHandle;
		MaterialHandle materialHandle;
		unsigned int startIndex, endIndex;
	};
	struct Vertex
	{
		float x;
		float y;
		float z;
	};

	struct Material
	{
		float Ns;					//Shininess of the material
		float Ka[3];				//Ambient color (r,g,b)

		float Ni;					//Reflection index
		float Kd[3];				//Diffuse color (r,g,b)

		float D;					//Transparency Tr (alpha)
		float Ks[3];				//Specular color (r,g,b)
		
		float Tf[3];				//Color Transperancy color (d or Tr)
		float Ke;					//Emissive color

		unsigned int Illum;					//Define the illumination model: illum = 1 a flat material with no specular highlights, illum = 2 denotes the presence of specular highlights

		std::string m_Map_Kd;		//diffuse
		std::string m_Map_Ka;		//ambient
		std::string m_Map_Ks;		//specular
		std::string m_Map_Ke;		//emissive fucked up shit
		std::string m_Map_Ns;		//specular shinyness
		std::string m_Map_D;		//transparency
		std::string m_Bump;			//normal map
		std::string m_Disp;			//displacment map
		std::string m_Occulsion;	//diffuse blackmap
	};

	typedef unsigned int Index;
}