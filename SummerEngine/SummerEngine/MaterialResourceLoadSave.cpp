#include "MaterialResourceLoadSave.h"
#include "Mesh.h"
#include "StreamFile.h"

Resource* MaterialResourceLoadSave::Load(std::string p_FileName)
{
	//load from file then load textures from dds?

	return nullptr; 
}
void MaterialResourceLoadSave::Save(Resource* p_File)
{

}

const char* MaterialResourceLoadSave::GetExtension()
{
	return ".mat";
}