#include "AdressTranslator.h"

AdressTranslator* AdressTranslator::m_Singleton = nullptr;

AdressTranslator* AdressTranslator::GetInstance()
{
	if (m_Singleton == nullptr)
	{
		m_Singleton = new AdressTranslator();
	}
	return m_Singleton;
}

AdressTranslator::AdressTranslator()
{
}


AdressTranslator::~AdressTranslator()
{
}


void AdressTranslator::AddAdress(void* p_OldAdress, void* p_NewAdress)
{
	m_AdressMap[(int)p_OldAdress] = (int)p_NewAdress;
}

void* AdressTranslator::Translate(int p_OldAdress)
{
	AdressTable::iterator t_It = m_AdressMap.find(p_OldAdress);
	if (t_It == m_AdressMap.end())
	{
		return nullptr;
	}
	return (void*)t_It->second;
}