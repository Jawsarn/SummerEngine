#include "DirectXGraphicEngine.h"
#include "TextureLoaderDDS.h"
#include "../IO/StreamFile.h"

//Creates a handle to a mesh resource in the eingine TODO::Save mesh into a binary file
MeshHandle DirectXGraphicEngine::CreateModel( const std::string& p_Name, std::vector<VertexPosNormalTexTangent>* p_Vertices, std::vector<Index>* p_Indicies )
{
	MeshInfo* t_NewMeshInfo = new MeshInfo();

	//Create the Vertex Buffer

	//description for vertex buffer
	D3D11_BUFFER_DESC t_BufferDesc;
	memset(&t_BufferDesc, 0, sizeof(D3D11_BUFFER_DESC));

	t_BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	t_BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	t_BufferDesc.CPUAccessFlags = 0;
	t_BufferDesc.MiscFlags = 0;
	t_BufferDesc.StructureByteStride = 0;
	t_BufferDesc.ByteWidth = sizeof(VertexPosNormalTexTangent)* p_Vertices->size();

	//add the data when creating
	D3D11_SUBRESOURCE_DATA t_Data;
	t_Data.pSysMem = &p_Vertices[0];
	t_Data.SysMemPitch = 0;
	t_Data.SysMemSlicePitch = 0;

	//create it
	HRESULT hr = m_Device->CreateBuffer(&t_BufferDesc, &t_Data, &t_NewMeshInfo->vertexBuffer);
	if (FAILED(hr))
	{
		//if failed return errormesh
		delete t_NewMeshInfo;
		return m_ErrorMeshID;
	}
		
	

	////Create the Index Buffer

	//change description to index
	t_BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	t_BufferDesc.ByteWidth = sizeof(UINT)* p_Indicies->size();

	//change data to index
	t_Data.pSysMem = &p_Indicies[0];
	
	// create it
	hr = m_Device->CreateBuffer(&t_BufferDesc, &t_Data, &t_NewMeshInfo->indexBuffer);
	if (FAILED(hr))
	{
		//if failed return errormesh
		delete t_NewMeshInfo;
		return m_ErrorMeshID;
	}
		

	//else we add it
	std::hash<MeshInfo*> t_Hasher;
	UINT t_Handle = t_Hasher(t_NewMeshInfo);

	//put it in our memory
	m_MeshKeys[t_Handle] = t_NewMeshInfo;

	//return handle
	return t_Handle;
}

//Creates a handle to a material resource in the engine TODO::change that we also check if there exist a material of this type TODO::Save material into a binary file
MaterialHandle DirectXGraphicEngine::CreateMaterial(const std::string& p_Name, Material* p_Mat)
{
	//copy over info to our directX material
	MaterialInfo* t_NewMaterial = new MaterialInfo(*p_Mat);

	//load textures
	t_NewMaterial->m_Map_Kd = LoadTexture(p_Mat->m_Map_Kd);
	t_NewMaterial->m_Map_Ka = LoadTexture(p_Mat->m_Map_Ka);
	t_NewMaterial->m_Map_Ks = LoadTexture(p_Mat->m_Map_Ks);
	t_NewMaterial->m_Map_Ke = LoadTexture(p_Mat->m_Map_Ke);
	t_NewMaterial->m_Map_Ns = LoadTexture(p_Mat->m_Map_Ns);
	t_NewMaterial->m_Map_D = LoadTexture(p_Mat->m_Map_D);
	t_NewMaterial->m_Bump = LoadTexture(p_Mat->m_Bump);
	t_NewMaterial->m_Disp = LoadTexture(p_Mat->m_Disp);
	t_NewMaterial->m_Occulsion = LoadTexture(p_Mat->m_Occulsion);

	//create buffer of the values
	D3D11_BUFFER_DESC t_BufferDesc;
	memset(&t_BufferDesc, 0, sizeof(D3D11_BUFFER_DESC));

	t_BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	t_BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	t_BufferDesc.CPUAccessFlags = 0;
	t_BufferDesc.MiscFlags = 0;
	t_BufferDesc.StructureByteStride = 0;
	t_BufferDesc.ByteWidth = sizeof(MaterialInfo::MaterialValues);

	HRESULT hr = m_Device->CreateBuffer(&t_BufferDesc, 0, &t_NewMaterial->m_MatBuffer);
	if (FAILED(hr))
	{
		//Failed, returning error material
		delete t_NewMaterial;
		return m_ErrorMaterialID;
	}


	//hash material to a key
	UINT key = t_MaterialHash(t_NewMaterial);
	
	m_MaterialKeys[key] = t_NewMaterial;

	return key;
}

//check if we have texture, else load it from approtpirate loader from extention, if error we use error image
TextureHandle DirectXGraphicEngine::LoadTexture(std::string p_Name)
{
	TextureIDMap::iterator t_TexIDMapIt = m_TextureIDMap.find(p_Name);

	//if we got the texure saved, return the ID to it
	if (t_TexIDMapIt != m_TextureIDMap.end())
	{
		return t_TexIDMapIt->second;
	}


	//else we find extension in filename to know what type it is
	std::size_t t_Spot = p_Name.find_last_of(".");
	std::string t_Extension;


	if (t_Spot == std::string::npos)
	{
		//no . found, that'd be an error filename
		t_Extension = "";
	}
	else
	{
		//create the extension to a string
		std::size_t t_Length = p_Name.length();
		t_Extension = p_Name.substr(t_Spot, t_Length);
	}

	HRESULT hr = S_OK;

	//find what type of file it is, and create it by the type
	ID3D11ShaderResourceView* t_NewResourceView;
	if (t_Extension == ".dds")
	{
		std::string t_FilePath = "Textures/" + p_Name;
		std::wstring t_LoadTextString = std::wstring(t_FilePath.begin(), t_FilePath.end());

		hr = CreateDDSTextureFromFile(m_Device, t_LoadTextString.c_str(), nullptr, &t_NewResourceView);
	}
	else
	{
		hr = E_FAIL;
	}

	//if the creaton failed, or no crator for the extention was found, we use errorimage, else we save the new texture to map, and hash a ID to it
	UINT o_ID;
	if (SUCCEEDED(hr))
	{
		std::hash<ID3D11ShaderResourceView*> t_Hasher;
		UINT t_Value = t_Hasher(t_NewResourceView);

		m_TextureMap[t_Value] = t_NewResourceView;
		m_TextureIDMap[p_Name] = t_Value;
		o_ID = t_Value;
	}
	else
	{
		//add ID to errorimage
		o_ID = m_ErrorTextureID;
	}

	return o_ID;
}

//Loads a mesh resource from file into the engine and returns a handle to it 
MeshHandle DirectXGraphicEngine::LoadModelFromFile(const std::string& p_Name)
{
	MeshIDMap::iterator t_MeshIDMap = m_MeshIDMap.find(p_Name);

	//if we got the mesh saved, return the ID to it
	if (t_MeshIDMap != m_MeshIDMap.end())
	{
		return t_MeshIDMap->second;
	}

	//else we load it
	IO::StreamFile *t_StreamFile = new IO::StreamFile();
	t_StreamFile->OpenFileRead(p_Name);

	//load vertices
	UINT t_NumOfVertice = IO::ReadUnsigned(*t_StreamFile);
	std::vector<VertexPosNormalTexTangent> t_Vertices;
	t_Vertices.resize(t_NumOfVertice);
	t_StreamFile->Read(t_NumOfVertice* sizeof(VertexPosNormalTexTangent), &t_Vertices[0]);

	//load indices
	UINT t_NumOfIndicies = IO::ReadUnsigned(*t_StreamFile);
	std::vector<UINT> t_Indicies;
	t_Indicies.resize(t_NumOfIndicies);
	t_StreamFile->Read(t_NumOfIndicies*sizeof(UINT), &t_Indicies[0]);

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////NOT DONE HEEEEEEEEEEEEEEREEEEEEEEEEEEEEE

	return m_ErrorMeshID;
}

//Loads a material resource from file into the engine and returns a handle to it
MaterialHandle DirectXGraphicEngine::LoadMaterialFromFile(const std::string& p_Name)
{
	MaterialIDMap::iterator t_MatIDMap = m_MaterialIDMap.find(p_Name);

	//if we got the material saved, return the ID to it
	if (t_MatIDMap != m_MeshIDMap.end())
	{
		return t_MatIDMap->second;
	}

	return m_ErrorMaterialID;
}
