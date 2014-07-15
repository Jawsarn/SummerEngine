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
	m_Position.resize(1);
	m_Normal.resize(1);
	m_TexCoord.resize(1);

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

		else if (type_str == "g" || type_str == "o")
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
		//next group
		m_CurrentGroup += 1;
		m_Position.resize(m_CurrentGroup + 1);
		m_Normal.resize(m_CurrentGroup + 1);
		m_TexCoord.resize(m_CurrentGroup + 1);
	}

	ObjGroups t_group;
	f >> t_group.name;
	m_groups.push_back(t_group);
}

void LoadObj::LoadFace(std::stringstream& f)
{
	//Example
	//f 2/1/1 3/2/1 4/3/1

	ObjGroups::Triangle t_triangle;
	std::string t_tri;//what's left
	std::string _new;//one index

	for (int i = 0; i < 3; i++)
	{
		//The first row
		f >> t_tri;
		for (int x = 0; x < 3; x++)
		{
			//First index
			_new = t_tri.substr(0, t_tri.find("/"));

			//Next index
			int t_next = (int)t_tri.find("/");
			if (t_next > 0)
				t_tri = t_tri.substr(t_next + 1);

			//Converting to int and also making sure that it's the same as the vector = (-1)
			t_triangle.index[i][x] = atoi(_new.c_str()) - 1;
		}
	}
	//Saving triangle
	m_groups[m_CurrentGroup].triangles.push_back(t_triangle);
}

void LoadObj::LoadMaterial(std::stringstream& g)
{
	//Load material file /data
}

void LoadObj::LoadPosition(std::stringstream& f)
{
	//int test = m_CurrentGroup;
	XMFLOAT3 t_pos;
	f >> t_pos.x >> t_pos.y >> t_pos.z;

	t_pos.z *= -1.0f;//
	m_Position[m_CurrentGroup].push_back(t_pos);
}

void LoadObj::LoadNormal(std::stringstream& f)
{
	XMFLOAT3 t_norm;
	f >> t_norm.x >> t_norm.y >> t_norm.z;

	t_norm.z *= -1.0f;//
	m_Normal[m_CurrentGroup].push_back(t_norm);
}

void LoadObj::LoadTexCoord(std::stringstream& f)
{
	XMFLOAT2 t_texCoord;
	f >> t_texCoord.x >> t_texCoord.y;

	t_texCoord.y = 1.0 - t_texCoord.y;//
	m_TexCoord[m_CurrentGroup].push_back(t_texCoord);
}

std::vector<XMFLOAT3> LoadObj::GetPositions(int p_GroupIndex)
{
	return m_Position[p_GroupIndex];
}

std::vector<XMFLOAT3> LoadObj::GetNormals(int p_GroupIndex)
{
	return m_Normal[p_GroupIndex];
}

std::vector<XMFLOAT2> LoadObj::GetTexCoords(int p_GroupIndex)
{
	return m_TexCoord[p_GroupIndex];
}

ObjGroups* LoadObj::GetGroup(int p_index)
{
	return &m_groups[p_index];
}

int LoadObj::GetGroupCount()
{
	return m_groups.size();
}
