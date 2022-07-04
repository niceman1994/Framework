#pragma once // 헤더파일 중복 방지용도(cpp파일에는 존재하지 않는다)

class MainUpdate
{
public:
	void Initialize();
	void Update();
	void Render();
	void Release();
public:
	MainUpdate();
	~MainUpdate();
};