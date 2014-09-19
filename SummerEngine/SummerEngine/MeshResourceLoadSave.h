#pragma once
#include "ResourceLoadSave.h"

/*Loads and Saves Meshes, note that this is not the same as the ObjLoader,
the Meshes saved here are optimiced with normalized edges and with binormal and tangent,
no Material data either, they should be seperate*/

class MeshResourceLoadSave : public ResourceLoadSave
{
public:
	virtual Resource* Load(std::string p_FileName);
	virtual void Save(Resource* p_File);
	virtual const char* GetExtension();
};

