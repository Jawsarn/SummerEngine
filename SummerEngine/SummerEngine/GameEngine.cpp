#include "GameEngine.h"


GameEngine* GameEngine::m_Singleton = nullptr;

GameEngine* GameEngine::GetInstance()
{
	if (m_Singleton == nullptr)
	{
		m_Singleton = new GameEngine();
	}

	return m_Singleton;
}

GameEngine::GameEngine()
{
	m_DeltaTime = new DOUBLE();
	m_GameTime = new DOUBLE();
	m_PrevTime = new ULONGLONG();

	*m_DeltaTime = 0;
	*m_GameTime = 0;
	*m_PrevTime = 0;
	m_RenderingSystem = nullptr;
}


GameEngine::~GameEngine()
{
}
#include "RenderComponent.h"
#include "ExtensibleGameFactory.h"


bool GameEngine::Start(UINT p_Width, UINT p_Height, HWND p_HandleWindow)
{
	Renderer* t_RendererStartup = t_RendererStartup->GetInstance();
	t_RendererStartup->Initialize(1920, 1080, p_HandleWindow);

	m_RenderingSystem = m_RenderingSystem->GetInstance();
	m_RenderingSystem->Start();


	

	return true;
}

void GameEngine::Destroy()
{

}

void GameEngine::Update()
{
	UpdateTime();
	//GetInput();
	//GetNetworkMessages();
	//SimulateWorld();
	//CollisionStep();
	//UpdateObjects();
	RenderWorld();
	//MiscTasks();
}

void GameEngine::UpdateTime()
{
	ULONGLONG timeCur = GetTickCount64();
	if (*m_PrevTime == 0)
		*m_PrevTime = timeCur;
	*m_DeltaTime = (timeCur - *m_PrevTime) / 1000.0f;
	*m_GameTime += *m_DeltaTime;
	*m_PrevTime = timeCur;
}

void GameEngine::GetInput()
{

}

void GameEngine::GetNetworkMessages()
{

}

void GameEngine::SimulateWorld()
{

}

void GameEngine::CollisionStep()
{

}

void GameEngine::UpdateObjects()
{

}

void GameEngine::RenderWorld()
{
	m_RenderingSystem->Update();
}

void GameEngine::MiscTasks()
{

}