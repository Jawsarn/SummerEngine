#include "System.h"


System::System()
{
	m_IsEnabled = true;		//always true, user can turn off if need
	this->Awake();			//to make sure Awake is always called
}


System::~System()
{
	this->Destroy();		//not sure if needed but it's good thing to always make sure destroy is awlays called
}

void System::Awake()
{

}

void System::Start()
{

}

void System::Update()
{

}

void System::Destroy()
{

}