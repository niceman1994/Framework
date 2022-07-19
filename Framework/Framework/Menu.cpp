#include "Menu.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "ObjectManager.h"
#include "CursorManager.h"

Menu::Menu() : Choose() { }
Menu::~Menu() { }

void Menu::Initialize()
{
	//Transform Info;

	Choose[0] = (char*)"1P ¢¹";

	Position = Vector3(77.0f, 24.0f);
}

void Menu::Update()
{
	DWORD dwKey = InputManager::GetInstance()->GetKey();

	if (dwKey & KEY_UP)
	{
		Position.y -= 2;
	
		if (Position.y <= 24.0f)
			Position = Vector3(77.0f, 24.0f);
	}
	
	if (dwKey & KEY_DOWN)
	{
		Position.y += 2;
	
		if (Position.y >= 30.0f)
			Position = Vector3(77.0f, 30.0f);
	}
	
	if (dwKey & KEY_ENTER)
	{
		if(Position.y == 24.0f)
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
	"\t\t\t\t      #### #####   #   ####   #####     #### #####   #   ##### #####     ####  ##### #     #####   ###  #####\n"
	"\t\t\t\t     #       #    # #  #   #    #      #       #    # #  #     #        #      #     #     #      #   #   #  \n"
	"\t\t\t\t    #        #   #   # #    #   #     #        #   #   # #     #       #       #     #     #      #       #  \n"
	"\t\t\t\t     #       #   #   # #   #    #      #       #   #   # #     #        #      #     #     #      #       #  \n"
	"\t\t\t\t      ###    #   ##### ####     #       ###    #   ##### # ### ####      ###   ####  #     ####   #       #  \n"
	"\t\t\t\t         #   #   #   # #  #     #          #   #   #   # #   # #            #  #     #     #      #       #  \n"
	"\t\t\t\t          #  #   #   # #   #    #           #  #   #   # #   # #             # #     #     #      #       #  \n"
	"\t\t\t\t         #   #   #   # #    #   #          #   #   #   # #   # #            #  #     #     #      #   #   #  \n"
	"\t\t\t\t     ####    #   #   # #     #  #      ####    #   #   #  #### #####    ####   ##### ##### #####   ###    #  \n", 7);

	CursorManager::GetInstance()->WriteBuffer(68.0f, 20.0f, (char*)"¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª", 8);

	for (int i = 0; i < 14; ++i)
	{
		CursorManager::GetInstance()->WriteBuffer(67.0f, 21.0f + i, (char*)
			"£ü\t\t\t\t\t     £ü\n", 8);
	}

	CursorManager::GetInstance()->WriteBuffer(85.0f, 24.0f, (char*)"STAGE 1", 3);
	CursorManager::GetInstance()->WriteBuffer(85.0f, 26.0f, (char*)"STAGE 2", 4);
	CursorManager::GetInstance()->WriteBuffer(85.0f, 28.0f, (char*)"STAGE 3", 6);
	CursorManager::GetInstance()->WriteBuffer(85.0f, 30.0f, (char*)"STAGE 4", 12);
	CursorManager::GetInstance()->WriteBuffer(82.0f, 49.0f, (char*)"ESC : µ¹¾Æ°¡±â");

	CursorManager::GetInstance()->WriteBuffer(68.0f, 34.0f, (char*)"¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª¡ª", 8);

	CursorManager::GetInstance()->WriteBuffer(Position.x, Position.y, Choose[0]);

	CursorManager::GetInstance()->WriteBuffer(152.0f, 49.0f, (char*)"CREDIT : ", 14);
	CursorManager::GetInstance()->WriteBuffer(161.0f, 49.0f, ObjectManager::GetInstance()->GetCredit(), 14);
}

void Menu::Release()
{

}
