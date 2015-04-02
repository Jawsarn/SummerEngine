#pragma once
#include <string>
#include "../Matrix/MatrixToolbox.h"

namespace SGEngine
{
	typedef unsigned int MeshHandle;
	typedef unsigned int MaterialHandle;
	typedef unsigned int TextureHandle;
	typedef unsigned int Index;
	typedef unsigned int ComponentHandle;

	//typedef unsigned int UINT;

	struct RenderObject
	{
		MeshHandle meshHandle;
		MaterialHandle materialHandle;
		Index startIndex, IndexAmount;
		MatrixHandle matrixHandle;
		ComponentHandle componentHandle;
		RenderObject()
		{
			meshHandle = 0;
			materialHandle = 0;
			startIndex = IndexAmount = 0;
			matrixHandle = 0;
			componentHandle = 0;
		}
		RenderObject(MeshHandle p_MeshHandle, MaterialHandle p_MaterialHandle, Index p_StartIndex,
			Index p_IndexAmount, MatrixHandle p_MatrixHandle, ComponentHandle p_ComponentHandle)
		{
			meshHandle = p_MeshHandle;
			materialHandle = p_MaterialHandle;
			startIndex = p_StartIndex;
			IndexAmount = p_IndexAmount;
			matrixHandle = p_MatrixHandle;
			componentHandle = p_ComponentHandle;
		}
		RenderObject(MeshHandle p_MeshHandle, MaterialHandle p_MaterialHandle, Index p_StartIndex,
			Index p_IndexAmount, MatrixHandle p_MatrixHandle)
		{
			meshHandle = p_MeshHandle;
			materialHandle = p_MaterialHandle;
			startIndex = p_StartIndex;
			IndexAmount = p_IndexAmount;
			matrixHandle = p_MatrixHandle;
			componentHandle = 0;
		}
	};

	struct Camera
	{
		MatrixHandle transformMatrixHandle;
		MatrixHandle projectionMatrixHandle;
		ComponentHandle componentHandle;
	};
	

	struct VertexPosNormalTex
	{
		VertexPosNormalTex()
		{
		}

		VertexPosNormalTex( Vec3 pos, Vec3 norm, Vec2 uv )
		{
			Position = pos;
			Normal = norm;
			TexCoord = uv;
		}

		Vec3 Position;
		Vec3 Normal;
		Vec2 TexCoord;
	};

	struct VertexPosNormalTangentTex
	{
		VertexPosNormalTangentTex()
		{
		}

		VertexPosNormalTangentTex(Vec3 pos, Vec3 norm, Vec3 tan, Vec2 uv )
		{
			Position = pos;
			Normal = norm;
			TexCoord = uv;
			Tangent = tan;
		}

		bool operator ==( const VertexPosNormalTangentTex& v )
		{
			return v.Position.x == Position.x && v.Position.y == Position.y && v.Position.z == Position.z
				&& v.TexCoord.x == TexCoord.x && v.TexCoord.y == TexCoord.y &&
				v.Normal.x == Normal.x && v.Normal.y == Normal.y && v.Normal.z == Normal.z &&
				v.Tangent.x == Tangent.x && v.Tangent.y == Tangent.y && v.Tangent.z == Tangent.z;
		}

		Vec3 Position;
		Vec3 Normal;
		Vec3 Tangent;
		Vec2 TexCoord;
	};

	struct VertexPos
	{
		VertexPos()
		{
		}

		VertexPos( Vec3 p )
		{
			Position = p;
		}

		VertexPos( const float x, const float y, const float z )
		{
			Position.x = x;
			Position.y = y;
			Position.z = z;
		}

		Vec3 Position;
	};

	struct VertexPosTex
	{
		VertexPosTex()
		{
		}

		VertexPosTex( Vec3 p, Vec2 t )
		{
			Position = p;
			TexCoord = t;
		}

		Vec3 Position;
		Vec2 TexCoord;
	};


	struct VertexPosNormal
	{
		VertexPosNormal()
		{
		}

		VertexPosNormal( Vec3 p, Vec3 n )
		{
			Position = p;
			Normal = n;
		}

		Vec3 Position;
		Vec3 Normal;
	};

	static bool CheckIfVertexExist( VertexPosNormalTangentTex* vertices, int numVertices, VertexPosNormalTangentTex v )
	{
		for( int i = 0; i < numVertices; i++ )
		{
			if( vertices[i] == v )
			{
				return true;
			}
		}
		return false;
	}

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

	
}