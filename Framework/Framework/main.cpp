// 2022.08.08 Framework Portfolio Ver 3.0
#define _CRT_SECURE_NO_WARNINGS
#include "Headers.h"
#include "MainUpdate.h"

// ��µǴ°� �������� GetTickCount64()�� �� ����ϱ⵵ ���� �ʱ�ȭ�Ǽ� ȭ���� ���� �����Ÿ���.
// �̸� �ذ��ϱ� ���ؼ��� ���۸� �߰��� ������ְ� ������Ʈ�� ��� ���ۿ� ����� ����ϴ� ���۷� �����Ѵ�.
// ���α׷��ֿ��� ������ �ּҸ� �ٲ� �� �ְ�, ������ �ּҰ� �ٲ��� �ʴ� ���� �ǹ��Ѵ�.
// static�� �����ؼ��� �ȵȴ�. ������ ���� ��� �ذ��ϱⰡ ��Ʊ� �����̴�.

int main(void)
{
	system("title ������ - Flight Shooting Game");

	system("mode con cols=180 lines=50"); // ������ 120, 30 ������� �����ִ� ��

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
