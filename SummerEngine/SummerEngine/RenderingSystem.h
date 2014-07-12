#pragma once
class RenderingSystem
{
public:
	RenderingSystem();
	~RenderingSystem();

	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void Destroy();

};

