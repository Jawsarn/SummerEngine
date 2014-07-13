#pragma once
#include "RenderingSystem.h"
#include "Renderer.h"


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

	RenderingSystem* m_RenderingSystem;
	ULONGLONG* m_PrevTime;
	DOUBLE* m_DeltaTime;
	DOUBLE* m_GameTime;
};

