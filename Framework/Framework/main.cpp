// 2022.07.05 Framework Ver 10.1 ( ObjectPool)
#define _CRT_SECURE_NO_WARNINGS
#include "Headers.h"
#include "MainUpdate.h"

// 출력되는게 많아지면 GetTickCount64()로 다 출력하기도 전에 초기화되서 화면이 많이 깜빡거린다.
// 이를 해결하기 위해서는 버퍼를 추가로 만들어주고 오브젝트를 담는 버퍼와 출력을 담당하는 버퍼로 구분한다.

int main(void)
{
	system("title 김정곤 - flight Shooting Game");

	system("mode con cols=120 lines=30"); // 강제로 120, 30 사이즈로 맞춰주는 것

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
