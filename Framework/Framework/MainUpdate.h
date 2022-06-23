#pragma once
class MainUpdate
{
private:
	int Count;
	SCENEID State;
public:
	void Initialize();
	void Update();
	void Render();
	void Release();
public:
	MainUpdate();
	~MainUpdate();
};