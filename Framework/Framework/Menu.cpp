#include "Menu.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "CursorManager.h"

Menu::Menu() { }
Menu::~Menu() { }

void Menu::Initialize()
{
	Text[0] = (char*)" #####  #######    #     #####  #######       #   ";
	Text[1] = (char*)"#     #    #      # #   #     # #            ##   ";
	Text[2] = (char*)"#          #     #   #  #       #           # #   ";
	Text[3] = (char*)" #####     #    #     # #  #### #####         #   ";
	Text[4] = (char*)"      #    #    ####### #     # #             #   ";
	Text[5] = (char*)"#     #    #    #     # #     # #             #   ";
	Text[6] = (char*)" #####     #    #     #  #####  #######     ##### ";
}

void Menu::Update()
{
	DWORD dwKey = InputManager::GetInstance()->GetKey();

	if (dwKey & KEY_ENTER)
		SceneManager::GetInstance()->SetScene(STAGEUI);

	if (dwKey & KEY_ESCAPE)
		SceneManager::GetInstance()->SetScene(LOGO);
		
	if (dwKey & KEY_0)
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
	"\t\t\t\t      #### #####   #   ####   #####     #### #####   #   ##### #####     ####  ##### #     #####   ###  #####\n"
	"\t\t\t\t     #       #    # #  #   #    #      #       #    # #  #     #        #      #     #     #      #   #   #  \n"
	"\t\t\t\t    #        #   #   # #    #   #     #        #   #   # #     #       #       #     #     #      #       #  \n"
	"\t\t\t\t     #       #   #   # #   #    #      #       #   #   # #     #        #      #     #     #      #       #  \n"
	"\t\t\t\t      ###    #   ##### ####     #       ###    #   ##### # ### ####      ###   ####  #     ####   #       #  \n"
	"\t\t\t\t         #   #   #   # #  #     #          #   #   #   # #   # #            #  #     #     #      #       #  \n"
	"\t\t\t\t          #  #   #   # #   #    #           #  #   #   # #   # #             # #     #     #      #       #  \n"
	"\t\t\t\t         #   #   #   # #    #   #          #   #   #   # #   # #            #  #     #     #      #   #   #  \n"
	"\t\t\t\t     ####    #   #   # #     #  #      ####    #   #   #  #### #####    ####   ##### ##### #####   ###    #  \n", 7);

	CursorManager::GetInstance()->WriteBuffer(60.0f, 20.0f, (char*)"―――――――――――――――――――――――――――――――", 8);

	for (int i = 0; i < 14; ++i)
	{
		CursorManager::GetInstance()->WriteBuffer(59.0f, 21.0f + i, (char*)
			"｜\t\t\t\t\t\t\t         ｜\n", 8);
	}

	for (int i = 0; i < 7; ++i)
		CursorManager::GetInstance()->WriteBuffer(67.0f, 24.0f + i, Text[i], 3);

	//CursorManager::GetInstance()->WriteBuffer(85.0f, 26.0f, (char*)"STAGE 2", 4);
	//CursorManager::GetInstance()->WriteBuffer(85.0f, 28.0f, (char*)"STAGE 3", 6);
	//CursorManager::GetInstance()->WriteBuffer(85.0f, 30.0f, (char*)"STAGE 4", 12);
	CursorManager::GetInstance()->WriteBuffer(82.0f, 49.0f, (char*)"ESC : 돌아가기");

	CursorManager::GetInstance()->WriteBuffer(60.0f, 34.0f, (char*)"―――――――――――――――――――――――――――――――", 8);

	CursorManager::GetInstance()->WriteBuffer(152.0f, 49.0f, (char*)"CREDIT : ", 14);
	CursorManager::GetInstance()->WriteBuffer(161.0f, 49.0f, ObjectManager::GetInstance()->GetCredit(), 14);
}

void Menu::Release()
{

}
