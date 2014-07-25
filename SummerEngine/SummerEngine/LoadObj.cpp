#include "LoadObj.h"

LoadObj::LoadObj()
{

}

LoadObj::~LoadObj()
{

}

bool LoadObj::Load(std::string p_fileName)
{
	//m_Obj.resize(1);
	m_CurrentObj = 0;//object with triangles and materials and pos,norm,texcoord
	m_CurrentGroup = 0;//group of triangles
	m_CurrentMaterial = 0;

	//m_Position.resize(1);
	//m_Normal.resize(1);
	//m_TexCoord.resize(1);

	std::ifstream t_file;
	t_file.open(p_fileName);

	if (!t_file.is_open())
	{
		std::string t_ErrorMessage = "Mesh: " + p_fileName + " could not be loaded";
		std::wstring t_covnvertText(t_ErrorMessage.begin(), t_ErrorMessage.end());
		MessageBox(nullptr, t_covnvertText.c_str(), L"Error-LoadObj", MB_ICONERROR | MB_OK);
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
			LoadMaterial(str_stream);
		}

		else if (type_str == "mtllib")
		{
			std::string t_MaterialFileName;
			int t_LastIndex = p_fileName.find_last_of(".");
			t_MaterialFileName = p_fileName.substr(0, t_LastIndex) + ".mtl";

			ParseMaterialFile(t_MaterialFileName);
		}
	}

	t_file.close();
	return true;
}

void LoadObj::LoadGroup(std::stringstream& f)
{
	if (m_Obj.size() > 0)
	{
		m_CurrentObj += 1;
	}

	m_Obj.resize(m_Obj.size() + 1);
	f >> m_Obj[m_CurrentObj].name;
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

			//Check if this is the first object that is loaded or not
			if (m_CurrentObj > 0)
			{
				//We are now loading an object that is after the first object, which means that this triangle index needs to be "reset"
				if (x == 0)
				{
					//Subtracting the triangle position-index by all the objects position count COMBINED
					int t_Result = 0;
					for (int y = m_CurrentObj; y > 0; y--)
					{
						t_Result += m_Obj[y - 1].m_Position.size();
					}

					int t_NewTriangleIndex = t_triangle.index[i][x] - t_Result;
					t_triangle.index[i][x] = t_NewTriangleIndex;
				}

				//Subtracting the triangle UV-index by all the objects texCoord count COMBINED
				if (x == 1)
				{
					int t_Result = 0;
					for (int y = m_CurrentObj; y > 0; y--)
					{
						t_Result += m_Obj[y - 1].m_TexCoord.size();
					}

					int t_NewTriangleIndex = t_triangle.index[i][x] - t_Result;
					t_triangle.index[i][x] = t_NewTriangleIndex;
				}

				//Subtracting the triangle normal-index by all the objects normal count COMBINED
				if (x == 2)
				{
					int t_Result = 0;
					for (int y = m_CurrentObj; y > 0; y--)
					{
						t_Result += m_Obj[y - 1].m_Normal.size();
					}

					int t_NewTriangleIndex = t_triangle.index[i][x] - t_Result;
					t_triangle.index[i][x] = t_NewTriangleIndex;
				}
			}
		}
	}
	//Saving triangle
	m_groups[m_CurrentGroup].triangles.push_back(t_triangle);
}

void LoadObj::LoadMaterial(std::stringstream& p_MaterialName)
{
	if (m_groups.size() > 0)
	{
		m_CurrentGroup += 1;
	}

	ObjGroups t_Group;
	p_MaterialName >> t_Group.material;
	//Saving obj id to the group
	t_Group.m_ObjId = m_CurrentObj;

	m_groups.push_back(t_Group);
	//sending id (so that object knows which groups that are in it)
	m_Obj[m_CurrentObj].m_GroupId.push_back(m_CurrentGroup);
}

bool LoadObj::ParseMaterialFile(std::string p_MaterialName)
{
	std::ifstream t_file;
	t_file.open(p_MaterialName);

	if (!t_file.is_open())
	{
		std::string t_ErrorMessage = "Material: " + p_MaterialName + " could not be loaded";
		std::wstring t_covnvertText(t_ErrorMessage.begin(), t_ErrorMessage.end());
		MessageBox(nullptr, t_covnvertText.c_str(), L"Error", MB_ICONERROR | MB_OK);
		return false;
	}

	std::string stream_line;

	while (std::getline(t_file, stream_line))
	{
		std::stringstream str_stream(stream_line);
		std::string type_str;
		str_stream >> type_str;

		Material::MaterialData* t_NewMaterial = nullptr;

		if (type_str == "newmtl")
		{

			if (m_Material.size() > 0)
			{
				m_CurrentMaterial += 1;
			}

			m_Material.resize(m_Material.size() + 1);

			std::string t_MaterialName;
			str_stream >> t_MaterialName;

			t_NewMaterial = new Material::MaterialData();
			t_NewMaterial->m_Name = t_MaterialName;
			m_Material[m_CurrentMaterial] = t_NewMaterial;

			//Map the material name to a material struct
			MAP_MATERIAL::const_iterator t_Iterate = m_MapMaterial.find(t_MaterialName);
			m_MapMaterial[t_MaterialName] = t_NewMaterial;
		}

		if (type_str == "Ns")
		{
			str_stream >> m_Material[m_CurrentMaterial]->m_Ns;
		}

		if (type_str == "Ka")
		{
			str_stream >> m_Material[m_CurrentMaterial]->m_Ka[0] >> m_Material[m_CurrentMaterial]->m_Ka[1] >> m_Material[m_CurrentMaterial]->m_Ka[2];
		}

		if (type_str == "Kd")
		{
			str_stream >> m_Material[m_CurrentMaterial]->m_Kd[0] >> m_Material[m_CurrentMaterial]->m_Kd[1] >> m_Material[m_CurrentMaterial]->m_Kd[2];
		}

		if (type_str == "Ks")
		{
			str_stream >> m_Material[m_CurrentMaterial]->m_Ks[0] >> m_Material[m_CurrentMaterial]->m_Ks[1] >> m_Material[m_CurrentMaterial]->m_Ks[2];
		}

		if (type_str == "Ni")
		{
			str_stream >> m_Material[m_CurrentMaterial]->m_Ni;
		}

		if (type_str == "d")
		{
			str_stream >> m_Material[m_CurrentMaterial]->m_D;
		}

		if (type_str == "illum")
		{
			str_stream >> m_Material[m_CurrentMaterial]->m_Illum;
		}

		if (type_str == "Ke")
		{
			str_stream >> m_Material[m_CurrentMaterial]->m_Ke;
		}

		//Textures
		if (type_str == "map_Ka")
		{
			str_stream >> m_Material[m_CurrentMaterial]->m_Map_Ka;
		}

		if (type_str == "map_Kd")
		{
			str_stream >> m_Material[m_CurrentMaterial]->m_Map_Kd;
		}

		if (type_str == "map_Ks")
		{
			str_stream >> m_Material[m_CurrentMaterial]->m_Map_Ks;
		}

		if (type_str == "map_Ke")
		{
			str_stream >> m_Material[m_CurrentMaterial]->m_Map_Ke;
		}

		if (type_str == "map_Ns")
		{
			str_stream >> m_Material[m_CurrentMaterial]->m_Map_Ns;
		}

		if (type_str == "map_d")
		{
			str_stream >> m_Material[m_CurrentMaterial]->m_Map_D;
		}

		if (type_str == "map_Bump")
		{
			str_stream >> m_Material[m_CurrentMaterial]->m_Bump;
		}
	}
	t_file.close();
	return true;
}

void LoadObj::LoadPosition(std::stringstream& f)
{
	//int test = m_CurrentGroup;
	XMFLOAT3 t_pos;
	f >> t_pos.x >> t_pos.y >> t_pos.z;

	t_pos.z *= -1.0f;//
	m_Obj[m_CurrentObj].m_Position.push_back(t_pos);
}

void LoadObj::LoadNormal(std::stringstream& f)
{
	XMFLOAT3 t_norm;
	f >> t_norm.x >> t_norm.y >> t_norm.z;

	t_norm.z *= -1.0f;//
	m_Obj[m_CurrentObj].m_Normal.push_back(t_norm);
}

void LoadObj::LoadTexCoord(std::stringstream& f)
{
	XMFLOAT2 t_texCoord;
	f >> t_texCoord.x >> t_texCoord.y;

	t_texCoord.y = 1.0 - t_texCoord.y;
	m_Obj[m_CurrentObj].m_TexCoord.push_back(t_texCoord);
}

std::vector<XMFLOAT3>& LoadObj::GetPositions(int p_ObjIndex)
{
	return m_Obj[p_ObjIndex].m_Position;
}

std::vector<XMFLOAT3>& LoadObj::GetNormals(int p_ObjIndex)
{
	return m_Obj[p_ObjIndex].m_Normal;
}

std::vector<XMFLOAT2>& LoadObj::GetTexCoords(int p_ObjIndex)
{
	return m_Obj[p_ObjIndex].m_TexCoord;
}

ObjGroups* LoadObj::GetGroup(int p_index)
{
	return &m_groups[p_index];
}

std::vector<ObjGroups> LoadObj::GetAllGroupsFromAMesh(int p_ObjIndex)
{
	std::vector<ObjGroups> t_Groups;
	//int t_ObjSize = m_Obj.size();
	int t_GroupSize = m_Obj[p_ObjIndex].m_GroupId.size();

	for (int x = 0; x < t_GroupSize; x++)
	{
		t_Groups.push_back(m_groups[m_Obj[p_ObjIndex].m_GroupId[x]]);
	}

	return t_Groups;
}

Material::MaterialData* LoadObj::GetMaterial(std::string p_MaterialData)
{
	MAP_MATERIAL::const_iterator t_Iterator = m_MapMaterial.find(p_MaterialData);
	if (t_Iterator == m_MapMaterial.end())
		return nullptr;
	else
		return t_Iterator->second;
}

int LoadObj::GetGroupCount()
{
	return m_groups.size();
}

int LoadObj::GetObjCount()
{
	return m_Obj.size();
}

std::vector<Material::MaterialData*> LoadObj::GetMaterials(int p_ObjIndex)
{
	std::vector<ObjGroups> t_Groups;
	int t_GroupSize = m_Obj[p_ObjIndex].m_GroupId.size();

	for (int x = 0; x < t_GroupSize; x++)
	{
		t_Groups.push_back(m_groups[m_Obj[p_ObjIndex].m_GroupId[x]]);
	}
	
	std::vector<Material::MaterialData*> t_MaterialData(t_GroupSize);
	for (int i = 0; i < t_GroupSize; i++)
	{
		t_MaterialData[i] = GetMaterial(t_Groups[i].material);
	}

	return t_MaterialData;
}

std::string LoadObj::GetMeshName(int p_ObjIndex)
{
	return m_Obj[p_ObjIndex].name;
}

