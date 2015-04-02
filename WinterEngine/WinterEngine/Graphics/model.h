#pragma once
#include <vector>
#include <string>
#include "GraphicToolbox.h"
#include <d3d11.h>
#include <directxmath.h>

namespace SGEngine
{
	struct Mesh
	{
		Mesh()
		{
			NumIndices = 0;
			StartIndex = 0;
		};

		unsigned int				StartIndex;
		int							NumIndices;
		std::string					MaterialName;
	};

	struct Model
	{
	public:
		Model()
		{
			NumVertices = 0;
			NumMeshes = 0;
			NumIndices = 0;
			Loaded = false;
			memset( BBoxMax, 0, sizeof( BBoxMax ) );
			memset( BBoxMin, 0, sizeof( BBoxMin ) );
		};

		std::string FileName;
		// should we have a name string as well?
		int			NumVertices;
		int			NumIndices;
		int			NumMeshes;
		float       World[4][4];
		bool		Loaded;

		float		BBoxMin[3];
		float		BBoxMax[3];

		std::vector<VertexPosNormalTangentTex> Vertices;
		std::vector<unsigned int>	Indices;

		// A model can have multiple meshes. (ex. one for each material)
		std::vector<Mesh> Meshes;
	};
}
