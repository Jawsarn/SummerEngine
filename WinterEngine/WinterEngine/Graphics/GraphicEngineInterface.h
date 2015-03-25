#pragma once

#include <Windows.h>
#include "GraphicToolbox.h"



using namespace SGEngine;
//question: should we have indexbuffers and vertexbuffers from the Game side, or have it as one object, 
//will we draw something without indexbuffer? if no, => one object, if yes, 2 objects..

#include <vector>
//functions that should be used towards the engine
class GraphicEngineInterface
{
public:
	
	~GraphicEngineInterface();

	//Getinstance of the engine, this will return the current selected type of engine directx/openGL
	static GraphicEngineInterface* GetInstance();




	//========================================\\
	///////=========Draw Functions=======\\\\\\\
	/////////=========================\\\\\\\\\\

	//Needs to be called befor all other drawcalls, and ended with "EndDraw()"
	virtual void BeginDraw() = 0;

	//Call "BeginDraw()" befor, draws nontransparent, call "ComputeDeferred()" after
	virtual void DrawOpaque(std::vector<RenderObject> p_RenderObects) = 0;

	//Computes deferrred rendering, call befor "DrawTransparent"
	virtual void ComputeDeferred() = 0;

	//Call after "ComputerDeferred()", draws transparent objects
	virtual void DrawTransparent(std::vector<RenderObject> p_RenderObects) = 0;

	//Call when done drawing, needs to be started with "BeginDraw()"
	virtual void EndDraw() = 0;

	//========================================\\
	///////==Create Resource Functions===\\\\\\\
	/////////=========================\\\\\\\\\\
	
	//Creates a handle to a mesh resource in the eingine
	virtual MeshHandle CreateMesh(std::vector<Vertex>* p_Vertices, std::vector<Index>* p_Indicies) = 0;

	//Creates a handle to a material resource in the engine
	virtual MaterialHandle CreateMaterial(Material* p_Mat) = 0;


	//========================================\\
	///////=========Initialization=======\\\\\\\
	/////////=========================\\\\\\\\\\

	//the parameter is for windows only
	virtual bool Initialize(HWND p_Handle, UINT p_Width, UINT p_Height) = 0;

	//after initialization, load a engine preset from file
	virtual bool LoadPresetFromFile() = 0;

	//========================================\\
	///////======Engine Functionality====\\\\\\\
	/////////=========================\\\\\\\\\\

	//Changes the resolution of a texture, 0 is the windowtexture
	void ChangeResolution(float p_Width, float p_Height, unsigned int p_Texture);

protected:
	GraphicEngineInterface();
	static GraphicEngineInterface* m_GraphicEngine;
/*functionality
//utility
add error-box / error-texture on resources that couldn't be loaded instead of crashing.

	

	//typical stuff
	Meshes
	Light
	ParticleSystem
	Terrain
	Shadows
	

*/
};

