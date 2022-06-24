// 2022.06.24 Framework Ver 2.1
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

const DWORD KEY_UP = 1;
const DWORD KEY_DOWN = 2;
const DWORD KEY_LEFT = 4;
const DWORD KEY_RIGHT = 8;
const DWORD KEY_SPACE = 16;
const DWORD KEY_ENTER = 32;
const DWORD KEY_CTRL = 64;
const DWORD KEY_ALT = 128;

// Singleton
/*
	데이터가 한 곳에만 있고 어디에서나 사용할 수 있어야 하는 것
	관리자처럼 사용한다. 그래서 하나만 만들고 생성자를 private으로 만든다
*/

int main(void)
{
	/*
	DWORD InputKey = 0;

	cout << "입력 : "; cin >> InputKey;

	if (InputKey & KEY_UP)
		cout << "KEY_UP" << endl;

	if (InputKey & KEY_DOWN)
		cout << "KEY_DOWN" << endl;

	if (InputKey & KEY_LEFT)
		cout << "KEY_LEFT" << endl;

	if (InputKey & KEY_RIGHT)
		cout << "KEY_RIGHT" << endl;

	if (InputKey & KEY_SPACE)
		cout << "KEY_SPACE" << endl;

	if (InputKey & KEY_ENTER)
		cout << "KEY_ENTER" << endl;

	if (InputKey & KEY_CTRL)
		cout << "KEY_CTRL" << endl;

	if (InputKey & KEY_ALT)
		cout << "KEY_ALT" << endl;
	*/

	
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