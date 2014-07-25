#pragma once
#include "System.h"
#include "Renderer.h"
#include "Entity.h"
#include "Editor.h"

class GameEngine
{
public:
	static GameEngine* GetInstance();

	bool Start(UINT p_Width, UINT p_Height, HWND p_HandleWindow);
	void Destroy();
	void Update();

private:
	GameEngine();
	~GameEngine();


	void UpdateTime();
	void GetInput();
	void GetNetworkMessages();
	void SimulateWorld();
	void CollisionStep();
	void UpdateObjects();
	void RenderWorld();
	void MiscTasks();

	static GameEngine* m_Singleton;

	


	//testsers
	std::vector<System*> m_Systems;

	//tempos
	Entity* m_EntityTest;

	Editor* m_Editor;
};

