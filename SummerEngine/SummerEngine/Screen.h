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
	void SetWidth(float p_Width);
	void SetHeight(float p_Height);
	void SetOrigin(float p_Width, float p_Height);
	void SetColor(XMFLOAT3 p_Color);
	void SetDirection(XMFLOAT2 p_Direction);
	void SetSpeed(float p_Speed);
	void SetIsRendered(bool p_IsRendered);
};

