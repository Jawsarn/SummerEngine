#include "MeshResourceLoadSave.h"
#include "Mesh.h"
#include "StreamFile.h"

Resource* MeshResourceLoadSave::Load(std::string p_FileName)
{
	Mesh* o_Mesh = new Mesh();

	StreamFile t_File = StreamFile();
	t_File.OpenFileRead(p_FileName);

	//vertex
	Mesh::VertexGroups t_Groups;

	int t_NumOfGroups = ReadInt(t_File);

	for (int i = 0; i < t_NumOfGroups; i++)
	{
		int t_NumOfVertices = ReadInt(t_File);
		std::vector<Mesh::MeshVertex> t_VertexGroup;
		
		t_VertexGroup.resize(t_NumOfVertices);

		t_File.Read(sizeof(Mesh::MeshVertex)*t_NumOfVertices, &t_VertexGroup[0]);

		t_Groups.push_back(t_VertexGroup);
	}

	//index
	Mesh::IndicesGroups t_IndexGroups;

	int t_NumOfIndecies = ReadInt(t_File);

	for (int i = 0; i < t_NumOfIndecies; i++)
	{
		int t_NumOfIndecies = ReadInt(t_File);
		
		std::vector<int> t_IndexGroup;

		t_IndexGroup.resize(t_NumOfIndecies);
		t_File.Read(sizeof(int)*t_NumOfIndecies, &t_IndexGroup[0]);
		t_IndexGroups.push_back(t_IndexGroup);
	}

	o_Mesh->SetVertexData(t_Groups);

	return o_Mesh; //add code to create a mesh from file here
}
void MeshResourceLoadSave::Save(Resource* p_File)
{
	StreamFile t_File = StreamFile();
	t_File.OpenFileWrite(p_File->GetName());
	
	Mesh* t_Mesh = (Mesh*)p_File;
	
	//vertex
	Mesh::VertexGroups* t_VertexGroups = t_Mesh->GetVertexData();

	int t_NumOfGroups = t_VertexGroups->size();
	WriteInt(t_File, t_NumOfGroups);
	
	for (int i = 0; i < t_NumOfGroups; i++)
	{
		int t_NumOfVertices = t_VertexGroups[i].size();
		WriteInt(t_File, t_NumOfVertices);

		t_File.Write(sizeof(Mesh::MeshVertex)*t_NumOfVertices, &t_VertexGroups[i][0]);
	}

	//index
	Mesh::IndicesGroups* t_IndexGroups = t_Mesh->GetIndexData();

	int t_NumOfIndecies = t_IndexGroups->size();
	WriteInt(t_File, t_NumOfIndecies);

	for (int i = 0; i < t_NumOfIndecies; i++)
	{
		int t_NumOfIndecies = t_IndexGroups[i].size();
		WriteInt(t_File, t_NumOfIndecies);

		t_File.Write(sizeof(int)*t_NumOfIndecies, &t_IndexGroups[i][0]);
	}

	//t_File.Write(); custom data hela vägen, men du måste veta hur den ser ut när du laddar in den på ett bra sätt
	//eller
	//WriteFloat(); //loopa tills du läst in allt
	
	t_File.Close();
}

const char* MeshResourceLoadSave::GetExtension()
{
	return ".mesh";
}