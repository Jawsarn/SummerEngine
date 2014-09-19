#pragma once
#include "ResourceLoadSave.h"

/*Loads and Saves textures ,atm only DDS*/

class TextureResourceLoadSave : public ResourceLoadSave
{
public:
	virtual Resource* Load(std::string p_FileName);
	virtual void Save(Resource* p_File);
	virtual const char* GetExtension();
};

