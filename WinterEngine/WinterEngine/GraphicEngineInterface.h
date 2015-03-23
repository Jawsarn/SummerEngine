#pragma once

namespace SGEngine
{
	

	typedef unsigned int MeshHandle;
	typedef unsigned int MaterialHandle;
	typedef unsigned int UINT;

	struct RenderObject
	{
		MeshHandle meshHandle;
		MaterialHandle materialHandle;
		UINT startIndex, endIndex;
	};
	struct Vertex
	{
		float x;
		float y;
		float z;
	};
	typedef unsigned int Index;
}

using namespace SGEngine;
//question: should we have indexbuffers and vertexbuffers from the Game side, or have it as one object, 
//will we draw something without indexbuffer? if no, => one object, if yes, 2 objects..

#include <vector>
//functions that should be used towards the engine
class GraphicEngineInterface
{
public:
	GraphicEngineInterface();
	~GraphicEngineInterface();


	//========================================\\
	///////=========Draw Functions=======\\\\\\\
	/////////=========================\\\\\\\\\\

	//Needs to be called befor all other drawcalls, and ended with "EndDraw()"
	void BeginDraw();

	//Call "BeginDraw()" befor, draws nontransparent, call "ComputeDeferred()" after
	void DrawOpaque(std::vector<RenderObject> p_RenderObects);

	//Computes deferrred rendering, call befor "DrawTransparent"
	void ComputeDeferred();

	//Call after "ComputerDeferred()", draws transparent objects
	void DrawTransparent(std::vector<RenderObject> p_RenderObects);

	//Call when done drawing, needs to be started with "BeginDraw()"
	void EndDraw();

	//========================================\\
	///////==Create Resource Functions===\\\\\\\
	/////////=========================\\\\\\\\\\

	//Creates a handle to a mesh resource in the eingine
	MeshHandle CreateMesh(std::vector<Vertex>* p_Vertices, std::vector<Index*> p_Indicies);

	//Creates a handle to a material resource in the engine
	MaterialHandle CreateMaterial();
	
	
	
/*functionality
//utility
add error-box / error-texture on resources that couldn't be loaded instead of crashing.

	

	//typical stuff
	Meshes
	Light
	ParticleSystem
	Terrain
	

*/
};

