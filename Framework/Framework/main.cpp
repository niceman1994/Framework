// 2022.06.24 Framework Ver 2.2
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Headers.h"
#include "MainUpdate.h"

using namespace std;

// Input

// 00000001 = 1
// 00000010 = 2
// 00000100 = 4
// 00001000 = 8
// 00010000 = 16
// 00100000 = 32
// 01000000 = 64
// 10000000 = 128

// Singleton
/*
	데이터가 한 곳에만 있고 어디에서나 사용할 수 있어야 하는 것
	관리자처럼 사용한다. 그래서 하나만 만들고 생성자를 private으로 만든다
*/

int main(void)
{
	MainUpdate Main;
	Main.Initialize();

	ULONGLONG Time = GetTickCount64(); // 1 / 1000 

	while (true)
	{
		if (Time + 50 < GetTickCount64())
		{
			Time = GetTickCount64();

			system("cls");

			Main.Update();
			Main.Render();
		}
	}
	
	return 0;
}