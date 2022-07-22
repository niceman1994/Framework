#include "Menu.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "CursorManager.h"

Menu::Menu() { }
Menu::~Menu() { }

void Menu::Initialize()
{
	count = 0;

	Text[0] = (char*)" #####  #######    #     #####  #######       ##   ";
	Text[1] = (char*)"#     #    #      # #   #     # #            # #   ";
	Text[2] = (char*)"#          #     #   #  #       #           #  #   ";
	Text[3] = (char*)" #####     #    #     # #  #### #####          #   ";
	Text[4] = (char*)"      #    #    ####### #     # #              #   ";
	Text[5] = (char*)"#     #    #    #     # #     # #              #   ";
	Text[6] = (char*)" #####     #    #     #  #####  #######     #######";

	Text[7] = (char*)" #####  #######    #     #####  #######      ##### ";
	Text[8] = (char*)"#     #    #      # #   #     # #           #     #";
	Text[9] = (char*)"#          #     #   #  #       #                 #";
	Text[10] = (char*)" #####     #    #     # #  #### #####        ##### ";
	Text[11] = (char*)"      #    #    ####### #     # #           #      ";
	Text[12] = (char*)"#     #    #    #     # #     # #           #      ";
	Text[13] = (char*)" #####     #    #     #  #####  #######     #######";

	Text[14] = (char*)" #####  #######    #     #####  #######      ##### ";
	Text[15] = (char*)"#     #    #      # #   #     # #           #     #";
	Text[16] = (char*)"#          #     #   #  #       #                 #";
	Text[17] = (char*)" #####     #    #     # #  #### #####        ##### ";
	Text[18] = (char*)"      #    #    ####### #     # #                 #";
	Text[19] = (char*)"#     #    #    #     # #     # #           #     #";
	Text[20] = (char*)" #####     #    #     #  #####  #######      ##### ";

	Text[21] = (char*)" #####  #######    #     #####  #######         ## ";
	Text[22] = (char*)"#     #    #      # #   #     # #              # # ";
	Text[23] = (char*)"#          #     #   #  #       #             #  # ";
	Text[24] = (char*)" #####     #    #     # #  #### #####        #   # ";
	Text[25] = (char*)"      #    #    ####### #     # #           #######";
	Text[26] = (char*)"#     #    #    #     # #     # #                # ";
	Text[27] = (char*)" #####     #    #     #  #####  #######          # ";
}

void Menu::Update()
{
	DWORD dwKey = InputManager::GetInstance()->GetKey();

	if (dwKey & KEY_DOWN)
	{
		count += 1;

		if (count >= 3)
			count = 3;
	}

	if (dwKey & KEY_UP)
	{
		count -= 1;

		if (count <= 0)
			count = 0;
	}

	if (dwKey & KEY_ENTER)
	{
		if (count == 0)
			SceneManager::GetInstance()->SetScene(STAGEUI);
	}

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
	CursorManager::GetInstance()->WriteBuffer(38.0f, 4.0f, (char*)
		"  #### #####   #   ####   #####     #### #####   #   ##### #####     ####  ##### #     #####   ###  #####  ", 7);
	CursorManager::GetInstance()->WriteBuffer(38.0f, 5.0f, (char*)
		" #       #    # #  #   #    #      #       #    # #  #     #        #      #     #     #      #   #   #  ", 7);
	CursorManager::GetInstance()->WriteBuffer(38.0f, 6.0f, (char*)
		"#        #   #   # #    #   #     #        #   #   # #     #       #       #     #     #      #       #  ", 7);
	CursorManager::GetInstance()->WriteBuffer(38.0f, 7.0f, (char*)
		" #       #   #   # #   #    #      #       #   #   # #     #        #      #     #     #      #       #  ", 7);
	CursorManager::GetInstance()->WriteBuffer(38.0f, 8.0f, (char*)
		"  ###    #   ##### ####     #       ###    #   ##### # ### ####      ###   ####  #     ####   #       #  ", 7);
	CursorManager::GetInstance()->WriteBuffer(38.0f, 9.0f, (char*)
		"     #   #   #   # #  #     #          #   #   #   # #   # #            #  #     #     #      #       #  ", 7);
	CursorManager::GetInstance()->WriteBuffer(38.0f, 10.0f, (char*)
		"      #  #   #   # #   #    #           #  #   #   # #   # #             # #     #     #      #       #  ", 7);
	CursorManager::GetInstance()->WriteBuffer(38.0f, 11.0f, (char*)
		"     #   #   #   # #    #   #          #   #   #   # #   # #            #  #     #     #      #   #   #  ", 7);
	CursorManager::GetInstance()->WriteBuffer(38.0f, 12.0f, (char*)
		" ####    #   #   # #     #  #      ####    #   #   #  #### #####    ####   ##### ##### #####   ###    #  ", 7);

	CursorManager::GetInstance()->WriteBuffer(60.0f, 20.0f, (char*)"―――――――――――――――――――――――――――――――", 8);

	for (int i = 0; i < 14; ++i)
	{
		CursorManager::GetInstance()->WriteBuffer(59.0f, 21.0f + i, (char*)
			"｜\t\t\t\t\t\t\t         ｜\n", 8);
	}

	if (count == 0)
	{
		for (int i = 0; i < 7; ++i)
			CursorManager::GetInstance()->WriteBuffer(66.0f, 24.0f + i, Text[i], 3);

		Sleep(200);
	}
	else if (count == 1)
	{
		for (int i = 7; i < 14; ++i)
			CursorManager::GetInstance()->WriteBuffer(66.0f, 17.0f + i, Text[i], 4);

		Sleep(200);
	}
	else if (count == 2)
	{
		for (int i = 14; i < 21; ++i)
			CursorManager::GetInstance()->WriteBuffer(66.0f, 10.0f + i, Text[i], 6);

		Sleep(200);
	}
	else if (count == 3)
	{
		for (int i = 21; i < 28; ++i)
			CursorManager::GetInstance()->WriteBuffer(66.0f, 3.0f + i, Text[i], 12);

		Sleep(200);
	}

	CursorManager::GetInstance()->WriteBuffer(82.0f, 49.0f, (char*)"ESC : 돌아가기");

	CursorManager::GetInstance()->WriteBuffer(60.0f, 34.0f, (char*)"―――――――――――――――――――――――――――――――", 8);

	CursorManager::GetInstance()->WriteBuffer(152.0f, 49.0f, (char*)"CREDIT : ", 14);
	CursorManager::GetInstance()->WriteBuffer(161.0f, 49.0f, ObjectManager::GetInstance()->GetCredit(), 14);
}

void Menu::Release()
{

}
