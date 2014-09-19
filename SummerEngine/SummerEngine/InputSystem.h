#pragma once
#include "System.h"
#include <map>
#include <DirectXMath.h>

/*Not used yet, saved for later. Due to the fact that this might be solved with scripting check the InputComponent.h for more notes*/

using namespace DirectX;

class InputSystem: public System
{
public:
	static InputSystem* GetInstance();

	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void Destroy();

private:
	InputSystem();
	~InputSystem();
	static InputSystem* m_Singleton;
	typedef std::map<char,std::vector<Component*>> KeyList;
	std::vector<Component*> MouseList;
	KeyList m_KeyWatchers;

	XMFLOAT2 m_LastMousePos;
};

