#pragma once
#include "Resource.h"

class ResourceLoadSave
{
public:
	virtual Resource* Load(std::string p_FileName) = 0;
	virtual void Save(Resource* p_File) = 0;
	virtual const char* GetExtension() = 0;
};

