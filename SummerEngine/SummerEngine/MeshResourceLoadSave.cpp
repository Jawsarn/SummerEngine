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
		int t_BytesToRead = sizeof(Mesh::MeshVertex)*t_NumOfVertices;
		int t_BytesRead = t_File.Read(sizeof(Mesh::MeshVertex)*t_NumOfVertices, &t_VertexGroup[0]);

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
		int t_BytesToRead = sizeof(int)*t_NumOfIndecies;

		int t_BytesToRead = t_File.Read(sizeof(int)*t_NumOfIndecies, &t_IndexGroup[0]);
		t_IndexGroups.push_back(t_IndexGroup);
	}

	o_Mesh->SetName(p_FileName);
	o_Mesh->SetIndexData(t_IndexGroups);
	o_Mesh->SetVertexData(t_Groups);

	o_Mesh->CreateMeshBuffers();
	

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
		int t_NumOfVertices = t_VertexGroups->at(i).size();
		WriteInt(t_File, t_NumOfVertices);

		int t_BytesToWrite = sizeof(Mesh::MeshVertex)*t_NumOfVertices;
		int t_SizeOfWrittenData = t_File.Write(sizeof(Mesh::MeshVertex)*t_NumOfVertices, &t_VertexGroups->at(i)[0]);
		int t_Break = 0;
	}

	//index
	Mesh::IndicesGroups* t_IndexGroups = t_Mesh->GetIndexData();

	int t_NumOfIndecies = t_IndexGroups->size();
	WriteInt(t_File, t_NumOfIndecies);

	for (int i = 0; i < t_NumOfIndecies; i++)
	{
		int t_NumOfIndecies = t_IndexGroups->at(i).size();
		WriteInt(t_File, t_NumOfIndecies);

		int t_BytesToWrite = sizeof(int)*t_NumOfIndecies;
		int t_SizeOfWrittenData = t_File.Write(sizeof(int)*t_NumOfIndecies, &t_IndexGroups->at(i)[0]);
		int t_Break = 0;
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