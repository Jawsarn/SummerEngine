#include "Entity.h"
#include "ExtensibleGameFactory.h"
#include "AdressTranslator.h"
#include <string>

Entity::Entity()
{
	m_Parent = nullptr;
	m_Name = "Entity";
}

Entity::Entity(std::string p_Name)
{
	m_Parent = nullptr;
	m_Name = p_Name;
}

Entity::Entity(const Entity &p_Copy)
{
	m_Parent = nullptr;
	m_Name = p_Copy.GetName();
	Initialize(p_Copy);
}

//Entity::Entity(const Entity &p_Copy, Entity* p_Parent)
//{
//	m_Parent = p_Parent;
//	Initialize(p_Copy);
//}
void Entity::Initialize(const Entity &p_Copy)
{
	int t_NumOfComponents = p_Copy.m_Components.size();

	ExtensibleGameFactory* t_Factory = t_Factory->GetInstance();

	for (int i = 0; i < t_NumOfComponents; i++)
	{
		this->m_Components.push_back(t_Factory->CreateComponent(p_Copy.m_Components[i]->GetName()));
	}

	this->m_EntityID = p_Copy.m_EntityID; //not sure if ID should follow? maybe not..
	this->m_Name = p_Copy.m_Name;

	int t_NumOfChildren = p_Copy.m_Children.size();

	for (int i = 0; i < t_NumOfChildren; i++)
	{
		Entity* t_NewChild = new Entity(*p_Copy.m_Children[i]);
		this->AddChild(t_NewChild);
	}
}

int Entity::GetID()
{
	return m_EntityID;
}

Entity::~Entity()
{
}

void Entity::AddComponent( Component *p_Component )
{
	if (p_Component->GetName() == "TransformComponent")
	{
		m_TransformComponent = p_Component;
	}
	else
	{
		m_Components.push_back(p_Component);
	}
	p_Component->SetEntity(this);
}

void Entity::SetParent(Entity *p_Parent)
{
	m_Parent = p_Parent;
}

void Entity::AddChild(Entity* p_Child)
{
	p_Child->SetParent(this);
	m_Children.push_back(p_Child);
}

std::vector<Entity*> Entity::GetChildren()
{
	return m_Children;
}

Entity* Entity::GetParent()
{
	return m_Parent;
}

Component* Entity::GetTransformComponent()
{
	return m_TransformComponent;
}



bool Entity::Read(Stream &p_Stream)
{
	m_Name = ReadString(p_Stream);

	m_EntityID = ReadInt(p_Stream);
	
	void* t_OldAdress = (void *)ReadInt(p_Stream); //this will be the previous adress
	AdressTranslator* t_AdrTranslator = t_AdrTranslator->GetInstance();
	t_AdrTranslator->AddAdress(t_OldAdress, this);

	int t_NumOfChildren = ReadInt(p_Stream);

	for (int i = 0; i < t_NumOfChildren; i++)
	{
		Entity* t_NewChild = new Entity();
		bool t_Success = t_NewChild->Read(p_Stream);
		if (!t_Success)
		{
			return t_Success;
		}
		AddChild(t_NewChild);
	}

	ExtensibleGameFactory* t_Factory = t_Factory->GetInstance(); //could just add this to the foor loop
	std::string t_TransformName = ReadString(p_Stream);
	Component* t_NewTranform = t_Factory->CreateComponent(t_TransformName);
	t_NewTranform->Read(p_Stream);
	AddComponent(t_NewTranform);

	int t_NumOfComponents = ReadInt(p_Stream);

	

	for (int i = 0; i < t_NumOfComponents; i++)
	{
		std::string t_ComponentType = ReadString(p_Stream);
		Component* t_NewComponent = t_Factory->CreateComponent(t_ComponentType);
		bool t_Success = t_NewComponent->Read(p_Stream);

		if (!t_Success)
		{
			return t_Success;
		}
		AddComponent(t_NewComponent);
	}
	return true;
}

bool Entity::Write(Stream &p_Stream)
{
	WriteString(p_Stream, m_Name);
	
	WriteInt(p_Stream, m_EntityID);

	WriteInt(p_Stream, (int)this); //change this to your adress, and give parent by load

	int t_NumOfChildren = m_Children.size();
	WriteInt(p_Stream, t_NumOfChildren);

	for (int i = 0; i < t_NumOfChildren; i++)
	{
		bool t_Success = m_Children[i]->Write(p_Stream);

		if (!t_Success)
		{
			return t_Success;
		}
	}

	bool t_Success = m_TransformComponent->Write(p_Stream);
	if (!t_Success)
	{
		return t_Success;
	}

	int t_NumOfComponents = m_Components.size();
	WriteInt(p_Stream, t_NumOfComponents);

	for (int i = 0; i < t_NumOfComponents; i++)
	{
		bool t_Success = m_Components[i]->Write(p_Stream);

		if (!t_Success)
		{
			return t_Success;
		}
	}

	return true;
}

void Entity::Fixup()
{
	//nothing needed here yet I think.. or maybe, go for a fixup through your components and children?
	int t_NumOfChildren = m_Children.size();
	for (int i = 0; i < t_NumOfChildren; i++)
	{
		m_Children[i]->Fixup();
	}

	int t_NumOfComponents = m_Components.size();
	for (int i = 0; i < t_NumOfComponents; i++)
	{
		m_Components[i]->Fixup();
	}
}

std::string Entity::GetName() const
{
	return m_Name;
}