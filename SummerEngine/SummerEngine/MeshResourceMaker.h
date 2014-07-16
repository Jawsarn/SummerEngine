#pragma once
#include "ResourceMaker.h"


class MeshResourceMaker:ResourceMaker
{
public:
	virtual Resource* Create(std::string p_FileName);
	virtual const char* GetExtension();
};

