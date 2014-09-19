#pragma once
#include "Resource.h"

/*abstract type for LoadSavers, this so that they all can be saved in a ResourceManager*/

class ResourceLoadSave
{
public:
	virtual Resource* Load(std::string p_FileName) = 0;
	virtual void Save(Resource* p_File) = 0;
	virtual const char* GetExtension() = 0;
};

