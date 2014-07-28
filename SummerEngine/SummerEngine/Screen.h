#pragma once
#include "Sprite.h"

class Screen : public Sprite
{
public:
	Screen();
	~Screen();
	Screen(std::string p_TextureName);

	virtual void Update(float p_DeltaTime);
	virtual void Draw();

	void SetPosition(XMFLOAT2 p_Position);
	void SetScale(float p_Scale);
	void SetColor(XMFLOAT4 p_Color);
	void SetDirection(XMFLOAT2 p_Direction);
	void SetSpeed(float p_Speed);
	void IsRendered(bool p_IsRendered);
};

