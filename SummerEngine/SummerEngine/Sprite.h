#pragma once
#include "Texture.h"
#include "Math.h"
#include "ResourceManager.h"
#include "Rect.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	Sprite(std::string p_TextureName);
	Texture* GetTexture();
	float GetSpeed();
	XMFLOAT2 GetDirection();
	XMFLOAT2 GetOrigin();
	XMFLOAT2 GetPosition();
	bool GetIsRender();
	Rect* GetCollisionBox();
	virtual void Update(float p_DeltaTime) = 0;
	virtual void Draw() = 0;

protected:
	Texture* m_Texture;
	XMFLOAT2 m_Origin;
	float m_Speed;
	XMFLOAT2 m_Position;
	float m_Scale;
	XMFLOAT4 m_Color;
	XMFLOAT2 m_Direction;
	bool m_IsRendered;
	void LoadContent(std::string p_TextureName);
	float GetScale();
};

