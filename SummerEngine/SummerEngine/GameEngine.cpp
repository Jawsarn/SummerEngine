#include "GameEngine.h"
#include "Time.h"

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
	
}


GameEngine::~GameEngine()
{
}


struct TestVector
{
	float a;
	float b;
	TestVector()
	{
		a = 0;
		b = 0;
	}
	TestVector(float p_a, float p_b)
	{
		a = p_a;
		b = p_b;
	}
};

#include "RenderComponent.h"
#include "ExtensibleGameFactory.h"
#include "StreamFile.h"
#include "Stream.h"
#include "RenderingSystem.h"
#include "LoadObj.h"
#include "Entity.h"
#include "CameraComponent.h"
#include "TransformComponent.h"
#include "ResourceManager.h"
#include "MeshResourceLoadSave.h"
#include "TextureResourceLoadSave.h"
#include "MaterialResourceLoadSave.h"


bool GameEngine::Start(UINT p_Width, UINT p_Height, HWND p_HandleWindow)
{
	//initialize Systems
	Renderer* t_RendererStartup = t_RendererStartup->GetInstance();
	t_RendererStartup->Initialize(1920, 1080, p_HandleWindow);

	RenderingSystem* t_RenderingSystem = t_RenderingSystem->GetInstance();
	CameraSystem* t_CameraSystem = t_CameraSystem->GetInstance();

	//push back systems in order to be updated
	m_Systems.push_back(t_CameraSystem);
	m_Systems.push_back(t_RenderingSystem);

	//startup everything
	for (int i = 0; i < m_Systems.size(); i++)
	{
		m_Systems[i]->Start();
	}

	//set up the ResourceManager
	ResourceManager* t_ResourceManager = t_ResourceManager->GetInstance();
	
	MeshResourceLoadSave* t_MeshResourceLoadSave = new MeshResourceLoadSave();
	TextureResourceLoadSave* t_TextureResourceLoadSave = new TextureResourceLoadSave();
	MaterialResourceLoadSave* t_MaterialResourceLoadSave = new MaterialResourceLoadSave();

	//register valid resources to the manager
	t_ResourceManager->Register(t_MeshResourceLoadSave);
	t_ResourceManager->Register(t_TextureResourceLoadSave);
	t_ResourceManager->Register(t_MaterialResourceLoadSave);


	//shouldn't be here untill later maybe? ... depends
	{
		m_EntityTest = new Entity();
		CameraComponent* t_NewComponent = new CameraComponent();
		t_NewComponent->SetLens(XM_PIDIV4, 1920.0f, 1080.0f, 0.5f, 10000.0f, 0, 0);

		TransformComponent* t_NewTransform = new TransformComponent();
		t_NewTransform->LookAt(XMFLOAT3(0, 0, 0), XMFLOAT3(0, 0, -1), XMFLOAT3(0, 1, 0));

		t_NewTransform->Update();

		m_EntityTest->AddComponent(t_NewComponent);
		m_EntityTest->SetTransformComponent(t_NewTransform);
	}
	m_Editor = new Editor();
	m_Editor->InitEditor();
	
	
	


	return true;
}



void GameEngine::Destroy()
{

}

void GameEngine::Update()
{
	//UpdateTime();
	//GetInput();
	//GetNetworkMessages();
	//SimulateWorld();
	//CollisionStep();
	//UpdateObjects();
	//RenderWorld();
	//MiscTasks();
	Time* t_Time = t_Time->GetInstace();
	t_Time->Update();

	for (int i = 0; i < m_Systems.size(); i++)
	{
		m_Systems[i]->Update();
	}
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
	
}

void GameEngine::MiscTasks()
{

}