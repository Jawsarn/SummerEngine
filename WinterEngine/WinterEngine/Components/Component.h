#pragma once

#include "../IO/Serializable.h"
#include <string>


class Component : IO::Serializable
{
public:
	Component();
	Component(std::string p_Name);
	~Component();

	//activate/deactivate component
	virtual bool IsEnabled() { return m_IsEnabled; }

	virtual void Enable();

	virtual void Disable();

	//should be called when enabled ? maybe same as constructor, could remove maybe
	virtual void Awake();

		//start the component, to do the work its supposd to
	virtual void Start();

	//pause the component
	virtual void Sleep();

	//update component, called from systems
	virtual void Update();

	//called when removing component
	virtual void Destroy();

	std::string GetName() const { return m_Name; }


	//IO
	virtual bool Read(IO::Stream &p_Stream);
	virtual bool Write(IO::Stream &p_Stream);

	//used to fix adress translations
	virtual void Fixup();

protected:
	//name of component to know what it is
	std::string m_Name;

	//if the component is active
	bool m_IsEnabled;
};



