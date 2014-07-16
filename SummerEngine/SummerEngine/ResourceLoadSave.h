#pragma once
#include "Resource.h"

class ResourceLoadSave
{
public:
	virtual Resource* Load(std::string p_FileName) = 0;
	virtual void Save(std::string p_FileName) = 0;
	virtual const char* GetExtension() = 0;
};

