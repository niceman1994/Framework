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
		exit(0);
}

void Logo::Render()
{
	CursorManager::GetInstance()->WriteBuffer(14.0f, 3.0f, (char*)
		"============================================================================================\n", 9);

	CursorManager::GetInstance()->WriteBuffer(0.0f, 4.0f,
		(char*)
		"	      ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"
		"	      ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"
		"	      88888888b:::::8888:::::8888:8888:::::::::d88888b::::888888888888::::::d8888888:888888888b:::\n"
		"	      8888:::Y888b::8888:::::8888:8888:::::::d888P::Y888b:::::8888:::::::::d88888888:8888:::Y888b:\n"
		"	      8888:::::8888:8888:::::8888:8888:::::::Y888b::::::::::::8888::::::::d888P88888:8888:::::8888\n"
		"	      8888:::d888P::8888:::::8888:8888::::::::Y8888b::::::::::8888:::::::d888P::8888:8888:::d888P:\n"
		"	      88888888P:::::8888:::::8888:8888::::::::::Y8888b::::::::8888::::::d888P:::8888:888888888b:::\n"
		"	      8888::::::::::8888:::::8888:8888:::::::::::::8888:::::::8888:::::d888888888888:8888:T888b:::\n"
		"	      8888::::::::::8888:::::8888:8888::::::::::::::8888::::::8888::::d888P:::::8888:8888::T888b::\n"
		"	      8888::::::::::Y888b:::d888P:8888:::::::Y888b::d888P:::::8888:::d888P::::::8888:8888:::T888b:\n"
		"	      8888::::::::::::Y8888888P:::888888888::::Y888888P:::::::8888::d888P:::::::8888:8888::::T888b\n"
		"	      ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n"
		"	      ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n", 12);
	
	CursorManager::GetInstance()->WriteBuffer(14.0f, 17.0f, (char*)
		"============================================================================================\n", 9);

	CursorManager::GetInstance()->WriteBuffer(52.0f, 21.0f, (char*)"0. 동전넣기", 6);
	CursorManager::GetInstance()->WriteBuffer(54.0f, 22.0f, (char*)"1. 시작", 2);
	CursorManager::GetInstance()->WriteBuffer(54.0f, 23.0f, (char*)"2. 종료", 8);
	
	CursorManager::GetInstance()->WriteBuffer(92.0f, 28.0f, (char*)"CREDIT : ", 14);
	CursorManager::GetInstance()->WriteBuffer(101.0f, 28.0f, (int)(char*)(ObjectManager::GetInstance()->GetCredit()), 14);
}

void Logo::Release()
{

}