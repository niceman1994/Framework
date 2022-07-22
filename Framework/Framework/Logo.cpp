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
	ObjectManager::GetInstance()->SetLife(3);

	Text[0] = (char*)"PPPPPPPPPPPPPPPPPP::::UUUUUUUU:::::UUUUUUUU:LLLLLLLLLLL:::::::::::::::::SSSSSSSSSSSSSS:::TTTTTTTTTTTTTTTTTTTTTTT::::::::::AAA::::::::::::::::RRRRRRRRRRRRRRRRR";
	Text[1] = (char*)"P:::::::::::::::::P:::U::::::U:::::U::::::U:L:::::::::L:::::::::::::::SS:::::::::::::::S:T:::::::::::::::::::::T:::::::::A:::A:::::::::::::::R:::::::::::::::RR";
	Text[2] = (char*)"P:::::::PPPPPP:::::P::U::::::U:::::U::::::U:L:::::::::L::::::::::::::S:::::SSSSSS::::::S:T:::::::::::::::::::::T::::::::A:::::A::::::::::::::R::::::RRRRRR:::::R";
	Text[3] = (char*)"PP::::::P     P:::::P:UU:::::U:::::U:::::UU:LL:::::::LL::::::::::::::S:::::S:::::SSSSSS::T:::::TT:::::::TT:::::T:::::::A:::::::A:::::::::::::RR:::::R:::::R:::::R";
	Text[4] = (char*)"  P:::::P     P:::::P::U:::::U:::::U:::::U:::L:::::L::::::::::::::::S:::::S::::::::::::::TTTTTT::T:::::T::TTTTTT::::::A:::::::::A::::::::::::::R::::R:::::R:::::R";
	Text[5] = (char*)"  P:::::P     P:::::P::U:::::D:::::D:::::U::::L:::::L::::::::::::::::S:::::S:::::::::::::::::::::T:::::T:::::::::::::A:::::A:::::A:::::::::::::R::::R:::::R:::::R";
	Text[6] = (char*)"  P:::::PPPPPP:::::P:::U:::::D:::::D:::::U::::L:::::L:::::::::::::::::S::::SSSS::::::::::::::::::T:::::T::::::::::::A:::::A:A:::::A::::::::::::R::::RRRRRR:::::R";
	Text[7] = (char*)"  P::::::::::::::PP::::U:::::D:::::D:::::U::::L:::::L::::::::::::::::::SS::::::SSSSS:::::::::::::T:::::T:::::::::::A:::::A:::A:::::A:::::::::::R:::::::::::::RR";
	Text[8] = (char*)"  P:::::PPPPPPPPP::::::U:::::D:::::D:::::U::::L:::::L::::::::::::::::::::SSS::::::::SS:::::::::::T:::::T::::::::::A:::::A:::::A:::::A::::::::::R::::RRRRRR:::::R";
	Text[9] = (char*)"  P:::::P::::::::::::::U:::::D:::::D:::::U::::L:::::L:::::::::::::::::::::::SSSSSS::::S::::::::::T:::::T:::::::::A:::::AAAAAAAAA:::::A:::::::::R::::R:::::R::::::R";
	Text[10] = (char*)"  P:::::P::::::::::::::U:::::D:::::D:::::U::::L:::::L:::::::::::::::::::::::::::::S:::::S::::::::T:::::T::::::::A:::::::::::::::::::::A::::::::R::::R:::::R::::::R";
	Text[11] = (char*)"  P:::::P::::::::::::::U::::::U:::U::::::U::::L:::::L:::::::::LLLLLL:::::::::::::::S:::::S:::::::T:::::T:::::::A:::::AAAAAAAAAAAAA:::::A:::::::R::::R:::::R::::::R";
	Text[12] = (char*)"PP:::::::PP::::::::::::U:::::::UUU:::::::U::LL:::::::LLLLLLLLL:::::L:::SSSSSS::::::S:::::S:::::TT:::::::TT::::A:::::A:::::::::::::A:::::A::::RR:::::R:::::R::::::R";
	Text[13] = (char*)"P:::::::::P:::::::::::::UU:::::::::::::UU:::L::::::::::::::::::::::L::S::::::SSSSSS::::S:::::::T:::::::::T:::A:::::A:::::::::::::::A:::::A:::R::::::R:::::R::::::R";
	Text[14] = (char*)"P:::::::::P:::::::::::::::UU:::::::::UU:::::L::::::::::::::::::::::L::S::::::::::::::SS::::::::T:::::::::T::A:::::A:::::::::::::::::A:::::A::R::::::R:::::R::::::R";
	Text[15] = (char*)"PPPPPPPPPP::::::::::::::::::UUUUUUUUU:::::::LLLLLLLLLLLLLLLLLLLLLLLL:::SSSSSSSSSSSSSSS:::::::::TTTTTTTTTTT:AAAAAAA:::::::::::::::::::AAAAAAA:RRRRRRRR:::::RRRRRR:R";
}

void Logo::Update()
{
	DWORD dwKey = InputManager::GetInstance()->GetKey();

	if (dwKey & KEY_0)
	{
		ObjectManager::GetInstance()->IncreaseCredit();
		CursorManager::GetInstance()->ClearBuffer();
		Sleep(100);

		if (ObjectManager::GetInstance()->GetCredit() >= 99)
			ObjectManager::GetInstance()->SetCredit(99);
	}

	if (dwKey & KEY_1 && ObjectManager::GetInstance()->GetCredit() >= 1)
		SceneManager::GetInstance()->SetScene(MENU);

	if (dwKey & KEY_2)
		SceneManager::GetInstance()->SetScene(MANUAL);

	if (dwKey & KEY_3)
		exit(0);
}

void Logo::Render()
{
	CursorManager::GetInstance()->WriteBuffer(8.0f, 5.0f, (char*)
		"=====================================================================================================================================================================\n", 9);

	for (int i = 0; i < 16; ++i)
		CursorManager::GetInstance()->WriteBuffer(10.0f, 6.0f + i, Text[i], 12);

	CursorManager::GetInstance()->WriteBuffer(8.0f, 22.0f, (char*)
		"=====================================================================================================================================================================\n:", 9);

	CursorManager::GetInstance()->WriteBuffer(84.0f, 32.0f, (char*)"0. 동전넣기", 6);
	CursorManager::GetInstance()->WriteBuffer(84.0f, 34.0f, (char*)"1. 시작", 2);
	CursorManager::GetInstance()->WriteBuffer(84.0f, 36.0f, (char*)"2. 조작법", 3);
	CursorManager::GetInstance()->WriteBuffer(84.0f, 38.0f, (char*)"3. 종료", 8);


	CursorManager::GetInstance()->WriteBuffer(152.0f, 49.0f, (char*)"CREDIT : ", 14);
	CursorManager::GetInstance()->WriteBuffer(161.0f, 49.0f, ObjectManager::GetInstance()->GetCredit(), 14);
}

void Logo::Release()
{

}