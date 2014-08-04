#pragma once
#include "Texture.h"
#include "Math.h"
#include "ResourceManager.h"
#include "Rect.h"

class Sprite
{
public:
	struct Vertex2D
	{
		XMFLOAT3 position;
		XMFLOAT2 texCoord;

		Vertex2D()
		{
			position = XMFLOAT3(0, 0, 0);
			texCoord = XMFLOAT2(0, 0);
		}
	};

	Sprite();
	~Sprite();

	Sprite(std::string p_TextureName);
	Texture* GetTexture();
	float GetSpeed();
	float GetScale();
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
};

