#pragma once
#include "Headers.h"

class CursorManager
{
public:
	static void SetCursorPosition(float _x, float _y)
	{
		COORD Pos = { (SHORT)_x, (SHORT)_y }; // COORD 구조체
		SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), Pos); // 표준 콘솔창에 있는 것(GetStdHandle(STD_OUTPUT_HANDLE))을 커서의 위치로 바꿔주는 함수
	}

	static void Draw(float _x, float _y, string _str)
	{
		SetCursorPosition(_x, _y);
		cout << _str;
	}
};

