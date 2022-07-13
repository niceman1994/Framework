#include "Menu.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "CursorManager.h"

Menu::Menu() { }
Menu::~Menu() { }

void Menu::Initialize()
{
	//Transform Info;

	Choose[0] = (char*)"1P ▷";

	Position = Vector3(60.0f, 22.0f);
}

void Menu::Update()
{
	DWORD dwKey = InputManager::GetInstance()->GetKey();

	if (dwKey & KEY_UP)
	{
		Position.y -= 2;
	
		if (Position.y <= 22.0f)
			Position = Vector3(60.0f, 22.0f);
	}
	
	if (dwKey & KEY_DOWN)
	{
		Position.y += 2;
	
		if (Position.y >= 28.0f)
			Position = Vector3(60.0f, 28.0f);
	}
	
	if (dwKey & KEY_ENTER)
	{
		if(Position.y == 22.0f)
			SceneManager::GetInstance()->SetScene(STAGEUI);
	}

	if (dwKey & KEY_ESCAPE)
		SceneManager::GetInstance()->SetScene(LOGO);
		
	if (dwKey & PRESS_0)
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
	"\t\t         #### #####   #   ####   #####     #### #####   #   ##### #####     ####  ##### #     #####   ###  #####\n"
	"\t\t        #       #    # #  #   #    #      #       #    # #  #     #        #      #     #     #      #   #   #  \n"
	"\t\t       #        #   #   # #    #   #     #        #   #   # #     #       #       #     #     #      #       #  \n"
	"\t\t        #       #   #   # #   #    #      #       #   #   # #     #        #      #     #     #      #       #  \n"
	"\t\t         ###    #   ##### ####     #       ###    #   ##### # ### ####      ###   ####  #     ####   #       #  \n"
	"\t\t            #   #   #   # #  #     #          #   #   #   # #   # #            #  #     #     #      #       #  \n"
	"\t\t             #  #   #   # #   #    #           #  #   #   # #   # #             # #     #     #      #       #  \n"
	"\t\t            #   #   #   # #    #   #          #   #   #   # #   # #            #  #     #     #      #   #   #  \n"
	"\t\t        ####    #   #   # #     #  #      ####    #   #   #  #### #####    ####   ##### ##### #####   ###    #  \n", 7);

	CursorManager::GetInstance()->WriteBuffer(68.0f, 22.0f, (char*)"STAGE 1", 3);
	CursorManager::GetInstance()->WriteBuffer(68.0f, 24.0f, (char*)"STAGE 2", 4);
	CursorManager::GetInstance()->WriteBuffer(68.0f, 26.0f, (char*)"STAGE 3", 6);
	CursorManager::GetInstance()->WriteBuffer(68.0f, 28.0f, (char*)"STAGE 4", 12);
	CursorManager::GetInstance()->WriteBuffer(68.0f, 39.0f, (char*)"ESC : 돌아가기");

	CursorManager::GetInstance()->WriteBuffer(Position.x, Position.y, Choose[0]);

	CursorManager::GetInstance()->WriteBuffer(118.0f, 39.0f, (char*)"CREDIT : ", 14);
	CursorManager::GetInstance()->WriteBuffer(127.0f, 39.0f, ObjectManager::GetInstance()->GetCredit(), 14);
}

void Menu::Release()
{

}
