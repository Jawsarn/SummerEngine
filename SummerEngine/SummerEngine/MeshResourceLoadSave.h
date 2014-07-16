#pragma once
#include "ResourceLoadSave.h"


class MeshResourceLoadSave :ResourceLoadSave
{
public:
	virtual Resource* Load(std::string p_FileName);
	virtual void Save(Resource* p_File);
	virtual const char* GetExtension();
};

