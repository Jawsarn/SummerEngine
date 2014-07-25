#include "Material.h"


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

void Material::SetMaterialData(MaterialData* p_MaterialData)
{
	m_MaterialData = p_MaterialData;
}

Material::MaterialData* Material::GetMaterialData()
{
	return m_MaterialData;
}

std::vector<Texture*> Material::GetTextures()
{
	return m_Textures;
}

void Material::SetFileName(std::string p_FileName)
{
	m_FileName = p_FileName;
}

void Material::SetTextures(std::vector<Texture*> p_Textures)
{
	m_Textures = p_Textures;
}
