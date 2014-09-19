#pragma once
#include "ResourceLoadSave.h"

/*Loads and Saves materials, see notes in MeshResourceLoadSave.h*/

class MaterialResourceLoadSave : public ResourceLoadSave
{
public:
	virtual Resource* Load(std::string p_FileName);
	virtual void Save(Resource* p_File);
	virtual const char* GetExtension();
};

