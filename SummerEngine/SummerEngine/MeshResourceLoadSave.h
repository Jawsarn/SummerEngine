#pragma once
#include "ResourceLoadSave.h"


class MeshResourceLoadSave :ResourceLoadSave
{
public:
	virtual Resource* Load(std::string p_FileName);
	virtual void Save(std::string p_FileName);
	virtual const char* GetExtension();
};

