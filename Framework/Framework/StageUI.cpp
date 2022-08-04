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
	count = 0;

	Text[0] = (char*)"8 888888888o   8 8888                  .8.   `8.`8888.      ,8' 8 888888888888  8 888888888o.         d8888";
	Text[1] = (char*)"8 8888    `88. 8 8888                 .888.   `8.`8888.    ,8'  8 8888          8 8888    `88.       d88888";
	Text[2] = (char*)"8 8888     `88 8 8888                :88888.   `8.`8888.  ,8'   8 8888          8 8888     `88          888";
	Text[3] = (char*)"8 8888     ,88 8 8888               . `88888.   `8.`8888.,8'    8 8888          8 8888     ,88          888";
	Text[4] = (char*)"8 8888.   ,88' 8 8888              .8. `88888.   `8.`88888'     8 888888888888  8 8888.   ,88'          888";
	Text[5] = (char*)"8 888888888P'  8 8888             .8`8. `88888.   `8. 8888      8 8888          8 888888888P'           888";
	Text[6] = (char*)"8 8888         8 8888            .8' `8. `88888.   `8 8888      8 8888          8 8888`8b               888";
	Text[7] = (char*)"8 8888         8 8888           .8'   `8. `88888.   8 8888      8 8888          8 8888 `8b.             888";
	Text[8] = (char*)"8 8888         8 8888          .888888888. `88888.  8 8888      8 8888          8 8888   `8b.           888";
	Text[9] = (char*)"8 8888         8 888888888888 .8'       `8. `88888. 8 8888      8 888888888888  8 8888     `88.       8888888";

	Text[10] = (char*)"########  ########    ###    ########  ##    ##";
	Text[11] = (char*)"##     ## ##         ## ##   ##     ##  ##  ## ";
	Text[12] = (char*)"##     ## ##        ##   ##  ##     ##   ####  ";
	Text[13] = (char*)"########  ######   ##     ## ##     ##    ##   ";
	Text[14] = (char*)"##   ##   ##       ######### ##     ##    ##   ";
	Text[15] = (char*)"##    ##  ##       ##     ## ##     ##    ##   ";
	Text[16] = (char*)"##     ## ######## ##     ## ########     ##   ";
}

void StageUI::Update()
{
	DWORD dwKey = InputManager::GetInstance()->GetKey();

	if (dwKey & KEY_ENTER)
		SceneManager::GetInstance()->SetScene(STAGE_1);
}

void StageUI::Render()
{
	for (int i = 0; i < 10; ++i)
		CursorManager::GetInstance()->WriteBuffer(36.0f, 7.0f + i, Text[i], 11);

	if (count <= 6)
	{
		++count;

		for (int i = 10; i < 17; ++i)
			CursorManager::GetInstance()->WriteBuffer(67.0f, 18.0f + i, Text[i], 14);
	}
	else if (count > 6)
	{
		++count;

		for (int i = 0; i < 7; ++i)
			CursorManager::GetInstance()->WriteBuffer(67.0f, 18.0f + i, Text[i], 0);

		if (count >= 17)
		{
			count = 0;
			return;
		}
	}
}

void StageUI::Release()
{

}
