#pragma once
#include <map>

/*Used to translate adresses(pointer) for saved and loaded objects. 
The adressTranslator holds a table with the adresses, so all the adresses first needs to be loaded, and then read.
Note that this might not be in use yet due to the fact that the "loading" and "saving" of objects at this moment is a recursive function and knows where its created*/

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

