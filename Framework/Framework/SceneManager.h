#pragma once
#include "Headers.h"

class Scene; // 정의 없이 만든 클래스다. 수학적으로 보면 허수와 같다.
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
	Scene* SceneState;
public:
	void SetScene(SCENEID _SceneState);
	void Update();
	void Render();
	void Release();
private:
	SceneManager();
public:
	~SceneManager();
};