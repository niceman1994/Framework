#include "SceneManager.h"

#include "Logo.h"
#include "Manual.h"
#include "Menu.h"
#include "StageUI.h"
#include "Stage_1.h"
#include "StageClear.h" // Scene.h ������ �߻�Ŭ������ ���� �߰��ص� �� �� ������ �Ļ� Ŭ�������� ��� ������ �߰��Ѵ�.

SceneManager* SceneManager::Instance = nullptr;

SceneManager::SceneManager() : SceneState(nullptr) {} // ������ ����Ǹ� �ʱ�ȭ�� �ݵ�� ���־�� �Ѵ�

SceneManager::~SceneManager() { Release(); }

void SceneManager::SetScene(SCENEID _SceneState)
{
	if (SceneState != nullptr)
		::Safe_Delete(SceneState); // �ƹ��͵� ���� ::(���ӽ����̽�)�� ���� ��� inline �Լ���� ���� �˸��� �ǹ��̴�.

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

	case SCENEID::STAGE_1:
		SceneState = new Stage_1;
		break;

	case SCENEID::STAGE_CLEAR:
		SceneState = new StageClear;
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
	::Safe_Delete(SceneState); // �����ؾ��� �� �ִٸ� ���������� ���� Release�Լ��� �ְ� �Ҹ��ڿ� �� Release�Լ��� �־��ָ� �ȴ�.
}