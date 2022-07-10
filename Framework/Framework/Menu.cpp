#include "Menu.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "CursorManager.h"

Menu::Menu() { }
Menu::~Menu() { }

void Menu::Initialize()
{
	Pointer[0] = (char*)">>>>>>>    ";
	Pointer[1] = (char*)"  >:::::>  ";
	Pointer[2] = (char*)"    >:::::>";
	Pointer[3] = (char*)"  >:::::>  ";
	Pointer[4] = (char*)">>>>>>>  	";
}

void Menu::Update()
{
	DWORD dwKey = InputManager::GetInstance()->GetKey();
		
	if (dwKey & KEY_ENTER)
		SceneManager::GetInstance()->SetScene(STAGE);

	if (dwKey & KEY_ESCAPE)
	{
		CursorManager::GetInstance()->ClearBuffer();
	}
		
	if (dwKey & PRESS_5)
	{
		ObjectManager::GetInstance()->IncreaseCredit();
		CursorManager::GetInstance()->ClearBuffer();
		Sleep(100);

		if (ObjectManager::GetInstance()->GetCredit() >= 99)
			ObjectManager::GetInstance()->SetCredit(99);
	}
}

void Menu::Render()
{
	CursorManager::GetInstance()->WriteBuffer(0.0f, 4.0f, (char*)
	"\n"
	"\t    #### #####   #    ###  #####    #### #####   #   ####  ####     #### #### #     ####  ### ##### \n" 
	"\t   #       #   #   # #   #   #     #       #   #   # #     #       #     #    #     #    #      #   \n" 
	"\t    ###    #   ##### ####    #      ###    #   ##### # ### ###      ###  ###  #     ###  #      #   \n" 
	"\t       #   #   #   # #   #   #         #   #   #   # #   # #           # #    #     #    #      #   \n" 
	"\t   ####    #   #   # #   #   #     ####    #   #   #  #### ####    ####  #### ##### ####  ###   #     "
	"\n");

	CursorManager::GetInstance()->WriteBuffer(0.0f, 13.0f, (char*)
		"\t\t\t\t _______  _______  _______  _______  _______    ____  \n"
		"\t\t\t\t|       ||       ||   _   ||       ||       |  |    | \n"
		"\t\t\t\t|  _____||_     _||  |_|  ||    ___||    ___|   |   | \n"
		"\t\t\t\t| |_____   |   |  |       ||   | __ |   |___    |   | \n"
		"\t\t\t\t|_____  |  |   |  |       ||   ||  ||    ___|   |   | \n"
		"\t\t\t\t _____| |  |   |  |   _   ||   |_| ||   |___    |   | \n"
		"\t\t\t\t|_______|  |___|  |__| |__||_______||_______|   |___| ");

	for (int i = 0; i < 2; ++i)
		CursorManager::GetInstance()->WriteBuffer(13.0f + i, 15.0f + i, Pointer[i]);
	for (int i = 2; i < 5; ++i)
		CursorManager::GetInstance()->WriteBuffer(17.0f - i, 15.0f + i, Pointer[i]);

	CursorManager::GetInstance()->WriteBuffer(110.0f, 25.0f, (char*)"\t\t\t\t\t\t\t\t\t\t\t\tCREDIT : \n\n\n\n");
	CursorManager::GetInstance()->WriteBuffer(89.0f, 25.0f, (int)(char*)(ObjectManager::GetInstance()->GetCredit()));
}

void Menu::Release()
{

}
