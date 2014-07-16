#include "MeshResourceLoadSave.h"
#include "Mesh.h"
#include "StreamFile.h"

Resource* MeshResourceLoadSave::Load(std::string p_FileName)
{
	return nullptr; //add code to create a mesh from file here
}
void MeshResourceLoadSave::Save(Resource* p_File)
{
	StreamFile t_File = StreamFile();
	t_File.OpenFileWrite(p_File->GetName());
	
	//t_File.Write(); custom data hela vägen, men du måste veta hur den ser ut när du laddar in den på ett bra sätt
	//eller
	//WriteFloat(); //loopa tills du läst in allt
	
	t_File.Close();
}

const char* MeshResourceLoadSave::GetExtension()
{
	return ".mesh";
}