#include "MeshResourceLoadSave.h"
#include "Mesh.h"
#include "StreamFile.h"
#include "Logger.h"

Resource* MeshResourceLoadSave::Load(std::string p_FileName)
{
	Mesh* o_Mesh = new Mesh();

	std::string t_FolderPath = "Graphics/Meshes/";
	StreamFile t_File = StreamFile();
	t_File.OpenFileRead(t_FolderPath + p_FileName);

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
		if (t_BytesToRead != t_BytesRead)
		{
			std::string t_Message = "Error loading Mesh Vertexdata " + p_FileName;
			//MessageBox(nullptr, t_Message.c_str(), L"ErrorMessage", MB_OK);
			Logger::Log( t_Message, "ResourceLoadSave", LoggerType::MSG_ERROR );
		}
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
		int t_BytesRead = t_File.Read(sizeof(int)*t_NumOfIndecies, &t_IndexGroup[0]);
		if (t_BytesToRead != t_BytesRead)
		{
			//std::wstring t_LoadTextString = std::wstring( p_FileName.begin(), p_FileName.end() );
			//std::wstring t_Message = L"Error loading Mesh Indexdata " + t_LoadTextString;
			//MessageBox( nullptr, t_Message.c_str(), L"ErrorMessage", MB_OK );

			Logger::Log( "Error loading Mesh Indexdata " + p_FileName , "ResourceLoadSave", LoggerType::MSG_ERROR );
		}
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
	std::string t_FolderPath = "Graphics/Meshes/";
	t_File.OpenFileWrite(t_FolderPath + p_File->GetName());
	
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
		if (t_BytesToWrite != t_SizeOfWrittenData)
		{
			std::string p_FileName = p_File->GetName();
			//std::wstring t_LoadTextString = std::wstring(p_FileName.begin(), p_FileName.end());
			//std::wstring t_Message = L"Error saving Mesh Vertexdata " + t_LoadTextString;
			//MessageBox(nullptr, t_Message.c_str(), L"ErrorMessage", MB_OK);
			Logger::Log( "Error saving Mesh Vertexdata " + p_FileName, "ResourceLoadSave", LoggerType::MSG_ERROR );
		}
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
		if (t_BytesToWrite != t_SizeOfWrittenData)
		{
			std::string p_FileName = p_File->GetName();
			//std::wstring t_LoadTextString = std::wstring(p_FileName.begin(), p_FileName.end());
			//std::wstring t_Message = L"Error saving Mesh Indexdata " + t_LoadTextString;
			//MessageBox(nullptr, t_Message.c_str(), L"ErrorMessage", MB_OK);
			Logger::Log( "Error saving Mesh Indexdata " + p_FileName, "ResourceLoadSave", LoggerType::MSG_ERROR );
		}
	}

	
	t_File.Close();
}

const char* MeshResourceLoadSave::GetExtension()
{
	return ".mesh";
}