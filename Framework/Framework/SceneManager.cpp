#include "SceneManager.h"

SceneManager* SceneManager::Instance = nullptr;

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
	
}

//const LOGO 
//const MENU
//const STAGE
//const EXIT

void SceneManager::SetScene(SCENEID _SceneState)
{
	switch (_SceneState)
	{
	case LOGO:
		cout << "LOGO" << endl;
		break;

	case MENU:
		cout << "MENU" << endl;
		break;

	case STAGE:
		cout << "STAGE" << endl;
		break;

	case EXIT:
		cout << "EXIT" << endl;
		break;
	}
}