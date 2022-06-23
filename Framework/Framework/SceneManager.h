#pragma once
#include "Headers.h"

class SceneManager
{
private:
	static SceneManager* Instance; // 포인터를 정적인 변수로 사용
public:
	static SceneManager* GetInstance()
	{
		if (Instance == nullptr)
			Instance = new SceneManager;

		return Instance;
	}
private:

public:
	void SetScene(int _SceneState);
private:
	SceneManager();
public:
	~SceneManager();
};