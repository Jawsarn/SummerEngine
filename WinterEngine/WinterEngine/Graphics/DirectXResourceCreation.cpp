#include "DirectXGraphicEngine.h"


//Creates a handle to a mesh resource in the eingine
MeshHandle DirectXGraphicEngine::CreateMesh(std::vector<Vertex>* p_Vertices, std::vector<Index>* p_Indicies)
{
	return 1;
}

//Creates a handle to a material resource in the engine
MaterialHandle DirectXGraphicEngine::CreateMaterial(Material* p_Mat)
{
	//copy over info to our directX material
	MaterialInfo* t_NewMaterial = new MaterialInfo(*p_Mat);

	return 1;
}