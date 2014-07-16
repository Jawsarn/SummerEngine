#pragma once
#include "Resource.h"

class ResourceMaker
{
public:
	virtual Resource* Create(std::string p_FileName) = 0;
	virtual const char* GetExtension() = 0;
};

