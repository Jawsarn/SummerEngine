#pragma once

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
	typedef unsigned int Index;
}