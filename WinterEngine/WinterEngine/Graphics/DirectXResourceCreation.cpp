#include "DirectXGraphicEngine.h"
#include "TextureLoaderDDS.h"


//Creates a handle to a mesh resource in the eingine
MeshHandle DirectXGraphicEngine::CreateModel( const std::string& p_Name, std::vector<VertexPosNormalTexTangent>* p_Vertices, std::vector<Index>* p_Indicies )
{
	return 1;
}

//Creates a handle to a material resource in the engine TODO::change that we also check if there exist a material of this type
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

	//hash material to a key
	UINT key = t_MaterialHash(t_NewMaterial);
	
	m_MaterialKeys[key] = t_NewMaterial;

	return key;
}

//check if we have texture, else load it from approtpirate loader from extention, if error we use error image
UINT DirectXGraphicEngine::LoadTexture(std::string p_Name)
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

		m_TextureMap[t_NewResourceView] = t_Value;
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