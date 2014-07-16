#pragma once
#include <map>

class AdressTranslator
{
public:
	static AdressTranslator* GetInstance();

	void AddAdress(void* p_OldAdress, void* p_NewAdress);
	void* Translate(int p_OldAdress);
	void Clear();

private:
	AdressTranslator();
	~AdressTranslator();

	static AdressTranslator* m_Singleton;
	typedef std::map<int, int> AdressTable;
	AdressTable m_AdressMap;
};

