#include "CameraSystem.h"

CameraSystem* CameraSystem::m_Singleton = nullptr;

CameraSystem* CameraSystem::GetInstance()
{
	if (m_Singleton == nullptr)
	{
		m_Singleton = new CameraSystem();
	}
	return m_Singleton;
}

CameraSystem::CameraSystem()
{
}


CameraSystem::~CameraSystem()
{
}


void CameraSystem::Awake()
{

}

void CameraSystem::Start()
{

}

void CameraSystem::Update()
{

}

void CameraSystem::Destroy()
{

}