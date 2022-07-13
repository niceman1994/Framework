#include "SceneManager.h"

#include "Logo.h"
#include "Manual.h"
#include "Menu.h"
#include "StageUI.h"
#include "Stage.h" // Scene.h 파일은 추상클래스로 만들어서 추가해도 쓸 수 없으니 파생 클래스들의 헤더 파일을 추가한다.

SceneManager* SceneManager::Instance = nullptr;

SceneManager::SceneManager() : SceneState(nullptr) {} // 변수가 선언되면 초기화는 반드시 해주어야 한다

SceneManager::~SceneManager() { Release(); }

void SceneManager::SetScene(SCENEID _SceneState)
{
	if (SceneState != nullptr)
		::Safe_Delete(SceneState); // 아무것도 없이 ::(네임스페이스)만 있을 경우 inline 함수라는 것을 알리는 의미이다.

	switch (_SceneState)
	{
	case SCENEID::LOGO:
		SceneState = new Logo;
		break;

	case SCENEID::MANUAL:
		SceneState = new Manual;
		break;

	case SCENEID::MENU:
		SceneState = new Menu;
		break;

	case SCENEID::STAGEUI:
		SceneState = new StageUI;
		break;

	case SCENEID::STAGE:
		SceneState = new Stage;
		break;

	case SCENEID::EXIT:
		exit(NULL);
		break;
	}

	SceneState->Initialize();
}

void SceneManager::Update()
{
	SceneState->Update();
}

void SceneManager::Render()
{
	SceneState->Render();
}

void SceneManager::Release()
{
	::Safe_Delete(SceneState); // 삭제해야할 게 있다면 삭제용으로 만든 Release함수에 넣고 소멸자에 이 Release함수를 넣어주면 된다.
}