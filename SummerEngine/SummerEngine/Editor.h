#pragma once
#include "Import.h"
#include "Entity.h"


class Editor
{
public:
	Editor();
	~Editor();
	void Release();
	void InitEditor();
	void Update();
	HRESULT Render(ID3D11DeviceContext* p_DeviceContext);

private:
	//Shader shader;//test
	Import* m_import;

	//test
	std::vector<Entity*> m_TestEntities;

	bool LoadTexture(std::string p_FileName,  Material::MaterialData* p_MaterialData);
};

