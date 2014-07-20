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