#include "Material.h"
#include "ResourceManager.h"

Material::Material()
{
}


Material::~Material()
{
}

void Material::SetName(std::string p_Name)
{
	m_FileName = p_Name;
}

const std::string Material::GetName()
{
	return m_FileName;
}

const Material::ResourceType Material::GetType() const
{
	return "Material";
}

void Material::LoadTextures()
{
	ResourceManager* t_ResourceManager = t_ResourceManager->GetInstance();


	if (m_Map_Kd != "")
	{
		Texture* t_NewTexture = (Texture*)t_ResourceManager->Create(m_Map_Kd);
		m_Textures["DIFFUSE"] = t_NewTexture;
	}
	if (m_Map_Ka != "")
	{
		Texture* t_NewTexture = (Texture*)t_ResourceManager->Create(m_Map_Ka);
		m_Textures["AMBIENT"] = t_NewTexture;
	}
	if (m_Map_Ks != "")
	{
		Texture* t_NewTexture = (Texture*)t_ResourceManager->Create(m_Map_Ks);
		m_Textures["SPECULAR"] = t_NewTexture;
	}
	if (m_Map_Ke != "")
	{
		Texture* t_NewTexture = (Texture*)t_ResourceManager->Create(m_Map_Ke);
		m_Textures["EMISSIVE"] = t_NewTexture;
	}
	if (m_Map_Ns != "")
	{
		Texture* t_NewTexture = (Texture*)t_ResourceManager->Create(m_Map_Ns);
		m_Textures["SHINYNESS"] = t_NewTexture;
	}
	if (m_Map_D != "")
	{
		Texture* t_NewTexture = (Texture*)t_ResourceManager->Create(m_Map_D);
		m_Textures["TRANSPARENCY"] = t_NewTexture;
	}
	if (m_Bump != "")
	{
		Texture* t_NewTexture = (Texture*)t_ResourceManager->Create(m_Bump);
		m_Textures["NORMAL"] = t_NewTexture;
	}
	if (m_Disp != "")
	{
		Texture* t_NewTexture = (Texture*)t_ResourceManager->Create(m_Disp);
		m_Textures["DISPLACEMENT"] = t_NewTexture;
	}
	if (m_Occulsion != "")
	{
		Texture* t_NewTexture = (Texture*)t_ResourceManager->Create(m_Occulsion);
		m_Textures["OCCLUSION"] = t_NewTexture;
	}
}


std::map<std::string, Texture*>* Material::GetTextures()
{
	return &m_Textures;
}

void Material::SetFileName(std::string p_FileName)
{
	m_FileName = p_FileName;
}
