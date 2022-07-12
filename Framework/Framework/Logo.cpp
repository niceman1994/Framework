#include "Logo.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "CursorManager.h"

#include "ObjectManager.h"
#include "Player.h"
#include "Enemy.h"

#include "Prototype.h"

Logo::Logo() { }
Logo::~Logo() { }


void Logo::Initialize()
{
	//ObjectManager::GetInstance()->AddObject(ObjectFactory<Player>::CreateObject());
	//SceneManager::GetInstance()->SetScene(STAGE);
}

void Logo::Update()
{
	DWORD dwKey = InputManager::GetInstance()->GetKey();

	if (dwKey & PRESS_1 && ObjectManager::GetInstance()->GetCredit() >= 1)
	{
		ObjectManager::GetInstance()->DecreaseCredit();
		SceneManager::GetInstance()->SetScene(MENU);
	}

	if ((dwKey & PRESS_5))
	{
		ObjectManager::GetInstance()->IncreaseCredit();
		CursorManager::GetInstance()->ClearBuffer();
		Sleep(100);

		if (ObjectManager::GetInstance()->GetCredit() >= 99)
			ObjectManager::GetInstance()->SetCredit(99);
	}
}

void Logo::Render()
{
	CursorManager::GetInstance()->WriteBuffer(0.0f, 0.0f,
		(char*)
		"		                                                                                \n"
		"		    8888888b   888     888 888      .d8888b. 88888888888     d88888 8888888b    \n"
		"		    888   Y88b 888     888 888     d88P  Y88b    888        d888888 888   Y88b  \n"
		"		    888    888 888     888 888     Y88b.         888       d88P8888 888     888 \n"
		"		    888   d88P 888     888 888      Y888b        888      d88P  888 888   d88P  \n"
		"		    8888888P   888     888 888         Y88b      888     d88P   888 8888888P  	\n"
		"		    888        888     888 888           888     888    d8888888888 888 T88b    \n"
		"		    888        Y88b   d88P 888     Y88b  d88P    888   d88P     888 888  T88b   \n"
		"		    888          Y88888P   88888888  Y8888P      888  d88P      888 888   T88b  \n"
		"		                                                                                \n");
	CursorManager::GetInstance()->WriteBuffer(15.0f, 10.0f, (char*)
		"==================================================================================\n");
	CursorManager::GetInstance()->WriteBuffer(0.0f, 11.0f, (char*)
		"		                                                                                  \n"
		"		  d8888b. db    db .d8888. db   db      .d8888. d888888b  .d8b.  d8888b. d888888b \n"
		"		  88  `8D 88    88 88'  YP 88   88      88'  YP `~~88~~' d8' `8b 88  `8D `~~88~~' \n"
		"		  88oodD' 88    88 `8bo.   88ooo88      `8bo.      88    88ooo88 88oobY'    88    \n"
		"		  88~~~   88    88   `Y8b. 88~~~88        `Y8b.    88    88~~~88 88`8b      88    \n"
		"		  88      88b  d88 db   8D 88   88      db   8D    88    88   88 88 `88.    88    \n"
		"		  88      ~Y8888P' `8888Y' YP   YP      `8888Y'    YP    YP   YP 88   YD    YP    \n"
		"\n"
		"\n");
	CursorManager::GetInstance()->WriteBuffer(0.0f, 30.0f, (char*)
		"			  ##:::::::'########:'##::::'##:'########:'##::::::::::'##::::##::\n"
		"			  ##::::::: ##.....:: ##:::: ##: ##.....:: ##:::::::::: ##:::'##::\n"
		"			  ##::::::: ##::::::: ##:::: ##: ##::::::: ##:::::::::: ##::: ##::\n"
		"			  ##::::::: ######::: ##:::: ##: ######::: ##:::::::::: ##::: ##::\n"
		"			  ##::::::: ##...::::. ##:: ##:: ##...:::: ##:::::::::: #########:\n"
		"			  ##::::::: ##::::::::. ## ##::: ##::::::: ##::::::::::...... ##::\n"
		"			  ########: ########:::. ###:::: ########: ########:::::::::: ##::\n");
	CursorManager::GetInstance()->WriteBuffer(0.0f, 30.0f, (char*)"\n\t\t\t\t\t\t\t\t\t\t\tCREDIT : ");
	CursorManager::GetInstance()->WriteBuffer(0.0f, 30.0f, (int)(char*)(ObjectManager::GetInstance()->GetCredit()));
}

void Logo::Release()
{

}