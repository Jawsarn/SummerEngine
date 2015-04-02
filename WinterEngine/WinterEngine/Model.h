#pragma once
#include <vector>
#include <string>
#include "Graphics/GraphicToolbox.h"
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
		std::vector<unsigned int>	Indices;
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
		};

		std::string Name;
		int			NumVertices;
		int			NumIndices;
		int			NumMeshes;
		float       World[4][4];
		bool		Loaded;

		std::vector<VertexPosNormalTangentTex> Vertices;

		// A model can have multiple meshes. (ex. one for each material)
		std::vector<Mesh> Meshes;
	};
}
