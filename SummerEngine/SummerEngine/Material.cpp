#include "Material.h"


Material::Material()
{
}


Material::~Material()
{
}

const std::string & Material::GetName() const
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
