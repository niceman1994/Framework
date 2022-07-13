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

	if (dwKey & PRESS_0)
	{
		ObjectManager::GetInstance()->IncreaseCredit();
		CursorManager::GetInstance()->ClearBuffer();
		Sleep(100);

		if (ObjectManager::GetInstance()->GetCredit() >= 99)
			ObjectManager::GetInstance()->SetCredit(99);
	}

	if (dwKey & PRESS_1 && ObjectManager::GetInstance()->GetCredit() >= 1)
	{
		ObjectManager::GetInstance()->DecreaseCredit();
		SceneManager::GetInstance()->SetScene(MENU);
	}

	if (dwKey & PRESS_2)
		SceneManager::GetInstance()->SetScene(MANUAL);

	if (dwKey & PRESS_3)
		exit(0);
}

void Logo::Render()
{
	CursorManager::GetInstance()->WriteBuffer(28.0f, 6.0f, (char*)
		"============================================================================================\n", 9);

	CursorManager::GetInstance()->WriteBuffer(0.0f, 7.0f,
		(char*)
		"\t\t	    ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"
		"\t\t	    ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"
		"\t\t	    88888888b:::::8888:::::8888:8888:::::::::d88888b::::888888888888::::::d8888888:888888888b:::\n"
		"\t\t	    8888:::Y888b::8888:::::8888:8888:::::::d888P::Y888b:::::8888:::::::::d88888888:8888:::Y888b:\n"
		"\t\t	    8888:::::8888:8888:::::8888:8888:::::::Y888b::::::::::::8888::::::::d888P88888:8888:::::8888\n"
		"\t\t	    8888:::d888P::8888:::::8888:8888::::::::Y8888b::::::::::8888:::::::d888P::8888:8888:::d888P:\n"
		"\t\t	    88888888P:::::8888:::::8888:8888::::::::::Y8888b::::::::8888::::::d888P:::8888:888888888b:::\n"
		"\t\t	    8888::::::::::8888:::::8888:8888:::::::::::::8888:::::::8888:::::d888888888888:8888:T888b:::\n"
		"\t\t	    8888::::::::::8888:::::8888:8888::::::::::::::8888::::::8888::::d888P:::::8888:8888::T888b::\n"
		"\t\t	    8888::::::::::Y888b:::d888P:8888:::::::Y888b::d888P:::::8888:::d888P::::::8888:8888:::T888b:\n"
		"\t\t	    8888::::::::::::Y8888888P:::888888888::::Y888888P:::::::8888::d888P:::::::8888:8888::::T888b\n"
		"\t\t	    ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"
		"\t\t	    ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n", 12);
	
	CursorManager::GetInstance()->WriteBuffer(28.0f, 20.0f, (char*)
		"============================================================================================\n", 9);

	CursorManager::GetInstance()->WriteBuffer(68.0f, 26.0f, (char*)"0. 동전넣기", 6);
	CursorManager::GetInstance()->WriteBuffer(68.0f, 28.0f, (char*)"1. 시작", 2);
	CursorManager::GetInstance()->WriteBuffer(68.0f, 30.0f, (char*)"2. 조작법", 3);
	CursorManager::GetInstance()->WriteBuffer(68.0f, 32.0f, (char*)"3. 종료", 8);
	
	CursorManager::GetInstance()->WriteBuffer(118.0f, 39.0f, (char*)"CREDIT : ", 14);
	CursorManager::GetInstance()->WriteBuffer(127.0f, 39.0f, ObjectManager::GetInstance()->GetCredit(), 14);
}

void Logo::Release()
{

}