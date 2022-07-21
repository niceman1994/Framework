#include "StageUI.h"
#include "CursorManager.h"
#include "SceneManager.h"
#include "InputManager.h"

StageUI::StageUI()
{
}

StageUI::~StageUI()
{
}

void StageUI::Initialize()
{
	Text[0] = (char*)"########  ########    ###    ########  ##    ##";
	Text[1] = (char*)"##     ## ##         ## ##   ##     ##  ##  ## ";
	Text[2] = (char*)"##     ## ##        ##   ##  ##     ##   ####  ";
	Text[3] = (char*)"########  ######   ##     ## ##     ##    ##   ";
	Text[4] = (char*)"##   ##   ##       ######### ##     ##    ##   ";
	Text[5] = (char*)"##    ##  ##       ##     ## ##     ##    ##   ";
	Text[6] = (char*)"##     ## ######## ##     ## ########     ##   ";

	Text[7] = (char*)"";
}

void StageUI::Update()
{
	DWORD dwKey = InputManager::GetInstance()->GetKey();

	if (dwKey & KEY_ENTER)
		SceneManager::GetInstance()->SetScene(STAGE);
}

void StageUI::Render()
{                
	CursorManager::GetInstance()->WriteBuffer(36.0f, 7.0f, (char*)
		"8 888888888o   8 8888                  .8.   `8.`8888.      ,8' 8 888888888888  8 888888888o.         d8888", 11);     
	CursorManager::GetInstance()->WriteBuffer(36.0f, 8.0f, (char*)
		"8 8888    `88. 8 8888                 .888.   `8.`8888.    ,8'  8 8888          8 8888    `88.       d88888", 11);
	CursorManager::GetInstance()->WriteBuffer(36.0f, 9.0f, (char*)
		"8 8888     `88 8 8888                :88888.   `8.`8888.  ,8'   8 8888          8 8888     `88          888", 11);
	CursorManager::GetInstance()->WriteBuffer(36.0f, 10.0f, (char*)
		"8 8888     ,88 8 8888               . `88888.   `8.`8888.,8'    8 8888          8 8888     ,88          888", 11);
	CursorManager::GetInstance()->WriteBuffer(36.0f, 11.0f, (char*)
		"8 8888.   ,88' 8 8888              .8. `88888.   `8.`88888'     8 888888888888  8 8888.   ,88'          888", 11);
	CursorManager::GetInstance()->WriteBuffer(36.0f, 12.0f, (char*)
		"8 888888888P'  8 8888             .8`8. `88888.   `8. 8888      8 8888          8 888888888P'           888", 11);
	CursorManager::GetInstance()->WriteBuffer(36.0f, 13.0f, (char*)
		"8 8888         8 8888            .8' `8. `88888.   `8 8888      8 8888          8 8888`8b               888", 11);
	CursorManager::GetInstance()->WriteBuffer(36.0f, 14.0f, (char*)
		"8 8888         8 8888           .8'   `8. `88888.   8 8888      8 8888          8 8888 `8b.             888", 11);
	CursorManager::GetInstance()->WriteBuffer(36.0f, 15.0f, (char*)
		"8 8888         8 8888          .888888888. `88888.  8 8888      8 8888          8 8888   `8b.           888", 11);
	CursorManager::GetInstance()->WriteBuffer(36.0f, 16.0f, (char*)
		"8 8888         8 888888888888 .8'       `8. `88888. 8 8888      8 888888888888  8 8888     `88.       8888888", 11);
	
	int count = 0;

	while (count <= 30)
	{
		for (int i = 0; i < 7; ++i)
			CursorManager::GetInstance()->WriteBuffer(67.0f, 28.0f + i, Text[i], 14);

		++count;

		//if (count % 2 == 1)
		//{
		//	for (int i = 0; i < 7; ++i)
		//		CursorManager::GetInstance()->WriteBuffer(67.0f, 28.0f + i, Text[i], 0);
		//}

		break;
	}
}

void StageUI::Release()
{
	
}
