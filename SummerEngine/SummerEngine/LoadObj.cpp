#include "LoadObj.h"

LoadObj::LoadObj()
{

}

LoadObj::~LoadObj()
{

}

bool LoadObj::Load(char* p_fileName)
{
	m_CurrentGroup = 0;
	std::ifstream t_file;
	t_file.open(p_fileName);

	if (!t_file.is_open())
	{
		//MessageBox(nullptr, L"Mesh could not be loaded", L"Error", MB_ICONERROR | MB_OK);
		return false;
	}

	std::string stream_line;

	while (std::getline(t_file, stream_line))
	{
		std::stringstream str_stream(stream_line);
		std::string type_str;
		str_stream >> type_str;

		if (type_str == "#" || type_str == "s")
		{
			//comment = ignore
			//ignoring smooth for now
		}

		else if (type_str == "v")
		{
			LoadPosition(str_stream);
		}

		else if (type_str == "vn")
		{
			LoadNormal(str_stream);
		}

		else if (type_str == "vt")
		{
			LoadTexCoord(str_stream);
		}

		else if (type_str == "g")
		{
			LoadGroup(str_stream);
		}

		else if (type_str == "f")
		{
			LoadFace(str_stream);
		}

		else if (type_str == "usemtl")
		{

		}
	}

	t_file.close();
	return true;
}

void LoadObj::LoadGroup(std::stringstream& f)
{
	if (m_groups.size() > 0)
	{
		m_CurrentGroup += 1;
	}

	ObjGroups t_group;
	f >> t_group.name;
	m_groups.push_back(t_group);

}

void LoadObj::LoadFace(std::stringstream& f)
{
	//f 2/1/1 3/2/1 4/3/1
}

void LoadObj::LoadPosition(std::stringstream& f)
{
	XMFLOAT3 t_pos;
	f >> t_pos.x >> t_pos.y >> t_pos.z;
	int a = 0;
	//m_groups[m_CurrentGroup].triangles.push_back()

}

void LoadObj::LoadNormal(std::stringstream& f)
{
	XMFLOAT3 t_norm;
	f >> t_norm.x >> t_norm.y >> t_norm.z;
}

void LoadObj::LoadTexCoord(std::stringstream& f)
{
	XMFLOAT2 t_texCoord;
	f >> t_texCoord.x >> t_texCoord.y;
}

XMFLOAT3& LoadObj::GetPosition(int p_index)
{
	return m_Position[p_index];
}

XMFLOAT3& LoadObj::GetNormal(int p_index)
{
	return m_Normal[p_index];
}

XMFLOAT3& LoadObj::GetTexCoord(int p_index)
{
	return m_TexCoord[p_index];
}