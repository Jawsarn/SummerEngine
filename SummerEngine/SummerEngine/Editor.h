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
private:
	Import* m_import;

	//	test
	std::vector<Entity*> m_TestEntities;

	bool LoadTexture(std::string p_FileName,  Material* p_MaterialData);
};

