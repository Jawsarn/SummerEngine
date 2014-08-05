#pragma once
#include "Import.h"
#include "Entity.h"
#include "ScreenManager.h"

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
	ScreenManager* m_ScreenManager;

	//	test
	std::vector<Entity*> m_TestEntities;

	bool LoadTexture(std::string p_FileName,  Material* p_MaterialData);
};

