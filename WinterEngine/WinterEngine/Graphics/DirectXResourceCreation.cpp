#include "DirectXGraphicEngine.h"
#include "TextureLoaderDDS.h"
#include "../IO/StreamFile.h"
#include "../Utility/Logger.h"

//Creates a handle to a mesh resource in the eingine TODO::Save mesh into a binary file
MeshHandle DirectXGraphicEngine::CreateModel( const std::string& p_Name, std::vector<VertexPosNormalTangentTex>* p_Vertices, std::vector<Index>* p_Indicies )
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
	t_BufferDesc.ByteWidth = sizeof(VertexPosNormalTangentTex)* p_Vertices->size();

	//add the data when creating
	D3D11_SUBRESOURCE_DATA t_Data;
	t_Data.pSysMem = &p_Vertices->at(0);
	t_Data.SysMemPitch = 0;
	t_Data.SysMemSlicePitch = 0;

	//create it
	HRESULT hr = m_Device->CreateBuffer(&t_BufferDesc, &t_Data, &t_NewMeshInfo->vertexBuffer);
	if (FAILED(hr))
	{
		//if failed return errormesh
		Logger::Log("Failed creating vertexbuffer for mesh \"" + p_Name + "\"", "DirectXRenderSystem", LoggerType::MSG_WARNING);

		delete t_NewMeshInfo;
		return m_ErrorMeshID;
	}
		
	

	////Create the Index Buffer

	//change description to index
	t_BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	t_BufferDesc.ByteWidth = sizeof(UINT)* p_Indicies->size();

	//change data to index
	t_Data.pSysMem = &p_Indicies->at(0);
	
	// create it
	hr = m_Device->CreateBuffer(&t_BufferDesc, &t_Data, &t_NewMeshInfo->indexBuffer);
	if (FAILED(hr))
	{
		//if failed return errormesh
		Logger::Log("Failed creating indexbuffer for mesh \"" + p_Name + "\"", "DirectXRenderSystem", LoggerType::MSG_WARNING);
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
	if (p_Mat->m_Map_Kd != "")
		t_NewMaterial->m_Map_Kd = LoadTexture(p_Mat->m_Map_Kd);
	if (p_Mat->m_Map_Ka != "")
		t_NewMaterial->m_Map_Ka = LoadTexture(p_Mat->m_Map_Ka);
	if (p_Mat->m_Map_Ks != "")
		t_NewMaterial->m_Map_Ks = LoadTexture(p_Mat->m_Map_Ks);
	if (p_Mat->m_Map_Ke != "")
		t_NewMaterial->m_Map_Ke = LoadTexture(p_Mat->m_Map_Ke);
	if (p_Mat->m_Map_Ns != "")
		t_NewMaterial->m_Map_Ns = LoadTexture(p_Mat->m_Map_Ns);
	if (p_Mat->m_Map_D != "")
		t_NewMaterial->m_Map_D = LoadTexture(p_Mat->m_Map_D);
	if (p_Mat->m_Bump != "")
		t_NewMaterial->m_Bump = LoadTexture(p_Mat->m_Bump);
	if (p_Mat->m_Disp != "")
		t_NewMaterial->m_Disp = LoadTexture(p_Mat->m_Disp);
	if (p_Mat->m_Occulsion != "")
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
		Logger::Log("Failed creating buffer for material \"" + p_Name + "\"", "DirectXRenderSystem", LoggerType::MSG_WARNING);
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
	ID3D11ShaderResourceView* t_NewResourceView;

	HRESULT hr = S_OK;

	if (t_Spot == std::string::npos)
	{
		//no . found, that'd be an error filename
		Logger::Log("Error in filename \"" + p_Name + "\" to load texture.", "DirectXRenderSystem", LoggerType::MSG_WARNING);
		t_Extension = "";
		hr = E_FAIL;
	}
	else
	{
		//create the extension to a string
		std::size_t t_Length = p_Name.length();
		t_Extension = p_Name.substr(t_Spot, t_Length);


		//find what type of file it is, and create it by the type
		
		if (t_Extension == ".dds")
		{
			std::string t_FilePath = "Textures/" + p_Name;
			std::wstring t_LoadTextString = std::wstring(t_FilePath.begin(), t_FilePath.end());

			hr = CreateDDSTextureFromFile(m_Device, t_LoadTextString.c_str(), nullptr, &t_NewResourceView);
			if (FAILED(hr))
				Logger::Log("Failed loading texture with DDS-loader from file \"" + p_Name + "\"", "DirectXRenderSystem", LoggerType::MSG_WARNING);

		}
		else
		{
			Logger::Log("Failed finding suitable texture-loader for extension \"" + t_Extension + "\" in filename \"" + p_Name + "\"", "DirectXRenderSystem", LoggerType::MSG_WARNING);
			hr = E_FAIL;
		}
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
bool DirectXGraphicEngine::LoadModel(const std::string& p_Name, MeshHandle* o_MeshHandle)
{
	MeshIDMap::iterator t_MeshIDMap = m_MeshIDMap.find(p_Name);

	//if we got the mesh saved, return the ID to it
	if (t_MeshIDMap != m_MeshIDMap.end())
	{
		*o_MeshHandle = t_MeshIDMap->second;
		return true;
	}

	//see if we have right extension to load it
	std::size_t t_Spot = p_Name.find_last_of(".");
	std::string t_Extension;

	


	if (t_Spot == std::string::npos)
	{
		//no . found, that'd be an error filename
		Logger::Log("Error in filename \"" + p_Name + "\" to load mesh.", "DirectXRenderSystem", LoggerType::MSG_WARNING);
		*o_MeshHandle = m_ErrorMeshID;
		return false;
	}
	else
	{
		//create the extension to a string
		std::size_t t_Length = p_Name.length();
		t_Extension = p_Name.substr(t_Spot, t_Length);


		if (t_Extension == ".smat")
		{
			//else we load it
			IO::StreamFile *t_StreamFile = new IO::StreamFile();
			bool t_Worked = t_StreamFile->OpenFileRead(p_Name);
			if (!t_Worked)
			{
				Logger::Log("Failed opening stream with filename \"" + p_Name + "\"", "DirectXRenderSystem", LoggerType::MSG_WARNING);
				delete t_StreamFile;
				*o_MeshHandle = m_ErrorMeshID;
				return false;
			}

			//load vertices
			UINT t_NumOfVertice = IO::ReadUnsigned(*t_StreamFile);
			std::vector<VertexPosNormalTangentTex> t_Vertices;
			t_Vertices.resize(t_NumOfVertice);
			t_StreamFile->Read(t_NumOfVertice* sizeof(VertexPosNormalTangentTex), &t_Vertices[0]);

			//load indices
			UINT t_NumOfIndicies = IO::ReadUnsigned(*t_StreamFile);
			std::vector<UINT> t_Indicies;
			t_Indicies.resize(t_NumOfIndicies);
			t_StreamFile->Read(t_NumOfIndicies*sizeof(UINT), &t_Indicies[0]);

			//close file
			t_StreamFile->Close();

			//create model
			UINT o_ID = CreateModel(p_Name, &t_Vertices, &t_Indicies);

			//clear list, dont think I need to do this but its good :)
			t_Vertices.clear();
			t_Indicies.clear();

			*o_MeshHandle = o_ID;
			return true;
		}
		else
		{
			Logger::Log("Failed finding suitable mesh-loader for extension \"" + t_Extension + "\" in filename \"" + p_Name + "\"", "DirectXRenderSystem", LoggerType::MSG_WARNING);
			*o_MeshHandle = m_ErrorMeshID;
			return false;
		}
	}
}

//Loads a material resource from file into the engine and returns a handle to it
MaterialHandle DirectXGraphicEngine::LoadMaterial(const std::string& p_Name)
{
	MaterialIDMap::iterator t_MatIDMap = m_MaterialIDMap.find(p_Name);

	//if we got the material saved, return the ID to it
	if (t_MatIDMap != m_MaterialIDMap.end())
	{
		return t_MatIDMap->second;
	}

	//see if we have right extension to load it
	std::size_t t_Spot = p_Name.find_last_of(".");
	std::string t_Extension;

	if (t_Spot == std::string::npos)
	{
		//no . found, that'd be an error filename
		Logger::Log("Error in filename \"" + p_Name + "\" to load material.", "DirectXRenderSystem", LoggerType::MSG_WARNING);
		
		return m_ErrorMaterialID;
	}

	//create the extension to a string
	std::size_t t_Length = p_Name.length();
	t_Extension = p_Name.substr(t_Spot, t_Length);

	if (t_Extension != ".smat")
	{
		Logger::Log("Failed finding suitable mat-loader for extension \"" + t_Extension + "\" in filename \"" + p_Name + "\"", "DirectXRenderSystem", LoggerType::MSG_WARNING);
		
		return m_ErrorMaterialID;
	}
	

	//else we load it
	IO::StreamFile *t_StreamFile = new IO::StreamFile();
	bool t_Worked = t_StreamFile->OpenFileRead(p_Name);
	if (!t_Worked)
	{
		Logger::Log("Failed opening stream with filename \"" + p_Name + "\"", "DirectXRenderSystem", LoggerType::MSG_WARNING);
		delete t_StreamFile;
		return m_ErrorMaterialID;
	}

	//load material
	UINT t_NumOfVertice = IO::ReadUnsigned(*t_StreamFile);
	SGEngine::Material* t_Material = new SGEngine::Material();
	

	//because of it including strings, we can't just read the material right of, we type our load instread TODO:: change niceer without including IO in the toolbox?
	t_Material->Ns = IO::ReadFloat(*t_StreamFile);
	t_Material->Ka[0] = IO::ReadFloat(*t_StreamFile);
	t_Material->Ka[1] = IO::ReadFloat(*t_StreamFile);
	t_Material->Ka[2] = IO::ReadFloat(*t_StreamFile);

	t_Material->Ni = IO::ReadFloat(*t_StreamFile);
	t_Material->Kd[0] = IO::ReadFloat(*t_StreamFile);
	t_Material->Kd[1] = IO::ReadFloat(*t_StreamFile);
	t_Material->Kd[2] = IO::ReadFloat(*t_StreamFile);

	t_Material->D = IO::ReadFloat(*t_StreamFile);
	t_Material->Ks[0] = IO::ReadFloat(*t_StreamFile);
	t_Material->Ks[1] = IO::ReadFloat(*t_StreamFile);
	t_Material->Ks[2] = IO::ReadFloat(*t_StreamFile);

	t_Material->Tf[0] = IO::ReadFloat(*t_StreamFile);
	t_Material->Tf[1] = IO::ReadFloat(*t_StreamFile);
	t_Material->Tf[2] = IO::ReadFloat(*t_StreamFile);
	t_Material->Ke = IO::ReadFloat(*t_StreamFile);

	t_Material->Illum = IO::ReadUnsigned(*t_StreamFile);

	t_Material->m_Map_Kd = IO::ReadString(*t_StreamFile);
	t_Material->m_Map_Ka = IO::ReadString(*t_StreamFile);
	t_Material->m_Map_Ks = IO::ReadString(*t_StreamFile);
	t_Material->m_Map_Ke = IO::ReadString(*t_StreamFile);
	t_Material->m_Map_Ns = IO::ReadString(*t_StreamFile);
	t_Material->m_Map_D = IO::ReadString(*t_StreamFile);
	t_Material->m_Bump = IO::ReadString(*t_StreamFile);
	t_Material->m_Disp = IO::ReadString(*t_StreamFile);
	t_Material->m_Occulsion = IO::ReadString(*t_StreamFile);


	//close file
	t_StreamFile->Close();

	//create model
	UINT o_ID = CreateMaterial(p_Name, t_Material);

	delete t_Material;

	return o_ID;
}

