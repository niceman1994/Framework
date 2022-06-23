// 2022.06.23 Framework Ver 1.2
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Headers.h"
#include "MainUpdate.h"

using namespace std;

// 클래스 내부에서 함수를 선언하면 인라인 함수처럼 사용된다.

// 11. 포인터 (복습) & 캡슐화
// 캡슐화 - 기능(함수)과 데이터를 묶어놓은 상태

// [포인터]
/*
	1. * : 데이터, & : 주소반환 연산자
	2. 포인터변수라면 [동적할당] - 확신이 없다면 동적할당부터 하는편이 좋다.
	3. 클래스와 구조체는 [.](점) 아니면 [->](화살표)로 접근
	4. [동적할당] 했다면 반드시 [할당해제] => 하지 않으면 메모리 누수가 발생한다.
*/

// inline 함수 - 먼저 실행시킬 수 있도록 도와주는 예약어
// const - 상수화 키워드, 값 변경을 하지 말라는 의미이기도 하다.
// & 사용 시기
/*
	※ 2항 연산일 경우
	1. &는 비트연산자의 역할을 하게된다.
	2. &&일 경우는 논리연산자 and의 역할을 하게 된다.

	※ 단항일 경우
	1. 항목 앞쪽에 쓰일 경우 주소 반환 연산자가 된다.
	2. 레퍼런스 연산자 - Call by Reference에서 파생된 의미
	값을 복사하는 것이 아닌 그 자체를 가져와서 사용하는 것이다.
*/

// GetTickCount 대략 49일
// GetTickCount64 대략 5억년

// Singleton
/*
	데이터가 한 곳에만 있고 어디에서나 사용할 수 있어야 하는 것
	관리자처럼 사용한다. 그래서 하나만 만들고 생성자를 private으로 만든다
*/

/*
class Singleton
{
private:
	static Singleton* Instance; // 포인터를 정적인 변수로 사용
public:
	static Singleton* GetInstance()
	{
		if (Instance == nullptr)
			Instance = new Singleton;

		return Instance;
	}
private:
	int Number;
public:
	int GetNumber() const { return Number; }
	void SetNumber(const int& _Number) { Number = _Number; }
private:
	Singleton() : Number(0) {}
public:
	~Singleton() {}
};

Singleton* Singleton::Instance = nullptr;
*/

int main(void)
{
	/*
	Singleton::GetInstance()->SetNumber(10);
	cout << Singleton::GetInstance()->GetNumber() << endl;
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