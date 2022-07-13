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
	
}

void StageUI::Update()
{
	DWORD dwKey = InputManager::GetInstance()->GetKey();

	if (dwKey & KEY_ENTER)
		SceneManager::GetInstance()->SetScene(STAGE);
}

void StageUI::Render()
{                
	CursorManager::GetInstance()->WriteBuffer(21.0f, 7.0f, (char*)
		"8 888888888o   8 8888                  .8.   `8.`8888.      ,8' 8 888888888888  8 888888888o.         d8888", 11);     
	CursorManager::GetInstance()->WriteBuffer(21.0f, 8.0f, (char*)
		"8 8888    `88. 8 8888                 .888.   `8.`8888.    ,8'  8 8888          8 8888    `88.       d88888", 11);
	CursorManager::GetInstance()->WriteBuffer(21.0f, 9.0f, (char*)
		"8 8888     `88 8 8888                :88888.   `8.`8888.  ,8'   8 8888          8 8888     `88          888", 11);
	CursorManager::GetInstance()->WriteBuffer(21.0f, 10.0f, (char*)
		"8 8888     ,88 8 8888               . `88888.   `8.`8888.,8'    8 8888          8 8888     ,88          888", 11);
	CursorManager::GetInstance()->WriteBuffer(21.0f, 11.0f, (char*)
		"8 8888.   ,88' 8 8888              .8. `88888.   `8.`88888'     8 888888888888  8 8888.   ,88'          888", 11);
	CursorManager::GetInstance()->WriteBuffer(21.0f, 12.0f, (char*)
		"8 888888888P'  8 8888             .8`8. `88888.   `8. 8888      8 8888          8 888888888P'           888", 11);
	CursorManager::GetInstance()->WriteBuffer(21.0f, 13.0f, (char*)
		"8 8888         8 8888            .8' `8. `88888.   `8 8888      8 8888          8 8888`8b               888", 11);
	CursorManager::GetInstance()->WriteBuffer(21.0f, 14.0f, (char*)
		"8 8888         8 8888           .8'   `8. `88888.   8 8888      8 8888          8 8888 `8b.             888", 11);
	CursorManager::GetInstance()->WriteBuffer(21.0f, 15.0f, (char*)
		"8 8888         8 8888          .888888888. `88888.  8 8888      8 8888          8 8888   `8b.           888", 11);
	CursorManager::GetInstance()->WriteBuffer(21.0f, 16.0f, (char*)
		"8 8888         8 888888888888 .8'       `8. `88888. 8 8888      8 888888888888  8 8888     `88.       8888888", 11);



	CursorManager::GetInstance()->WriteBuffer(52.0f, 23.0f, (char*)
		"########  ########    ###    ########  ##    ##\n", 14);
	CursorManager::GetInstance()->WriteBuffer(52.0f, 24.0f, (char*)
		"##     ## ##         ## ##   ##     ##  ##  ## \n", 14);
	CursorManager::GetInstance()->WriteBuffer(52.0f, 25.0f, (char*)
		"##     ## ##        ##   ##  ##     ##   ####  \n", 14);
	CursorManager::GetInstance()->WriteBuffer(52.0f, 26.0f, (char*)
		"########  ######   ##     ## ##     ##    ##   \n", 14);
	CursorManager::GetInstance()->WriteBuffer(52.0f, 27.0f, (char*)
		"##   ##   ##       ######### ##     ##    ##   \n", 14);
	CursorManager::GetInstance()->WriteBuffer(52.0f, 28.0f, (char*)
		"##    ##  ##       ##     ## ##     ##    ##   \n", 14);
	CursorManager::GetInstance()->WriteBuffer(52.0f, 29.0f, (char*)
		"##     ## ######## ##     ## ########     ##   \n", 14);
}

void StageUI::Release()
{
	
}
