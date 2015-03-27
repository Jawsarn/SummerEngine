#pragma once
#include <string>

namespace SGEngine
{
	typedef unsigned int MeshHandle;
	typedef unsigned int MaterialHandle;
	typedef unsigned int TextureHandle;
	typedef unsigned int MatrixHandle;
	typedef unsigned int Index;

	//typedef unsigned int UINT;

	struct RenderObject
	{
		MeshHandle meshHandle;
		MaterialHandle materialHandle;
		Index startIndex, endIndex;
		MatrixHandle matrixHandle;
		
	};

	struct Vec3
	{
		float x;
		float y;
		float z;

		Vec3()
		{
			x = 0; y = 0; z = 0;
		}
		Vec3( float _x, float _y, float _z )
		{
			x = _x; y = _y; z = _z;
		}
	};

	struct Vec2
	{
		float x;
		float y;
		Vec2()
		{
			x = 0; y = 0;
		}
		Vec2( float _x, float _y )
		{
			x = _x; y = _y;
		}
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

	struct VertexPosNormalTexTangent
	{
		VertexPosNormalTexTangent()
		{
		}

		VertexPosNormalTexTangent( Vec3 pos, Vec3 norm, Vec2 uv, Vec3 tan )
		{
			Position = pos;
			Normal = norm;
			TexCoord = uv;
			Tangent = tan;
		}

		bool operator ==( const VertexPosNormalTexTangent& v )
		{
			return v.Position.x == Position.x && v.Position.y == Position.y && v.Position.z == Position.z
				&& v.TexCoord.x == TexCoord.x && v.TexCoord.y == TexCoord.y &&
				v.Normal.x == Normal.x && v.Normal.y == Normal.y && v.Normal.z == Normal.z &&
				v.Tangent.x == Tangent.x && v.Tangent.y == Tangent.y && v.Tangent.z == Tangent.z;
		}

		Vec3 Position;
		Vec3 Normal;
		Vec2 TexCoord;
		Vec3 Tangent;
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

	static bool CheckIfVertexExist( VertexPosNormalTexTangent* vertices, int numVertices, VertexPosNormalTexTangent v )
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