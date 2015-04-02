#pragma once

#include <Windows.h>
#include "GraphicToolbox.h"


#define g_GraphicEngine GraphicEngineInterface::GetInstance()

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
	virtual void DrawOpaque(std::vector<RenderObject*>* p_RenderObects) = 0;

	//Computes deferrred rendering, call befor "DrawTransparent"
	virtual void ComputeDeferred() = 0;

	//Call after "ComputerDeferred()", draws transparent objects
	virtual void DrawTransparent(std::vector<RenderObject*>* p_RenderObects) = 0;

	//Call when done drawing, needs to be started with "BeginDraw()"
	virtual void EndDraw() = 0;

	//========================================\\
	///////==Create Resource Functions===\\\\\\\
	/////////=========================\\\\\\\\\\
	
	//Creates a handle to a mesh resource in the eingine
	virtual MeshHandle CreateModel( const std::string& p_Name, std::vector<VertexPosNormalTangentTex>* p_Vertices, std::vector<Index>* p_Indicies ) = 0;

	//Creates a handle to a material resource in the engine
	virtual MaterialHandle CreateMaterial(const std::string& p_Name, Material* p_Mat) = 0;

	//Loads a mesh resource from file into the engine and returns a handle to it
	virtual bool LoadModel( const std::string& p_Name, MeshHandle* o_MeshHandle, UINT& indexAmount /* TODO find nicer way?*/ ) = 0;

	//Loads a material resource from file into the engine and returns a handle to it
	virtual MaterialHandle LoadMaterial(const std::string& p_Name) = 0;


	//========================================\\
	///////=========Initialization=======\\\\\\\
	/////////=========================\\\\\\\\\\

	//the parameter is for windows only
	virtual bool Initialize(HWND p_Handle, UINT p_Width, UINT p_Height) = 0;

	//after initialization, load a engine preset from file
	virtual bool LoadPresetFromFile() = 0;


	//========================================\\
	///////=======Utility Functions======\\\\\\\
	/////////=========================\\\\\\\\\\

	//Changes the resolution of a texture, 0 is the windowtexture
	void ChangeResolution(float p_Width, float p_Height, unsigned int p_Texture);

	virtual void UseCamera(SGEngine::Camera p_Camera, UINT p_Slot) = 0;

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

