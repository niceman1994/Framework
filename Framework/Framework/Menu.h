#pragma once
#include "Scene.h" 

class Menu : public Scene
{
private:
	Vector3 Position;
	char* Select[36];
public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render()override;
	virtual void Release()override;
public:
	Menu();
	virtual ~Menu();
};

