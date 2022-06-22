// Framework Ver 0.3

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Parent/Parent.h"
#include "Parent/Child/Child.h"
#include "Parent/Child/Bullet.h"

using namespace std;

// 클래스 - 집합이기도 하고 설명서라고 할 수 있다.
// 오브젝트 - 클래스로 만들어져 있다.
// static은 정적변수라 런타임전에 올라간다. 런타임 이후에는 스택과 힙이 올라간다.

// 1. 정보은닉 - 객체지향의 시작, 객체에 대한 구체적인 정보를 노출시키지 않도록 하는 기법																										
/*
	수정이 불가능하게 특정 정보를 숨기는 것을 정보은닉이라고 한다. / 변경에 대비하는 설계
	(변경될 가능성이 있는 것들을 숨겨서 함부로 접근하지 못하게 한다)

	※ 특징
	1. 객체 간의 구체적인 결합도를 약화시켜 기능의 교체나 변경이 쉽도록 함.
	2. 동일한 타입의 다른 구현 객체들을 교체함으로써 동적 기능 변경이 가능함.
	3. 연동할 구체적인 구현이 없는 상태에서도 (인터페이스 만으로) 정확한 연동 코드의 생성이 가능함

	private : 자기 자신만 사용 가능.
	protected : 상속간의 공개된 상태. 비상속 클래스 사용불가. 외부 사용 불가.
	public : 공개된 상태
*/

// 2. 캡슐화
/*
	데이터(변수)와 기능(함수)을 묶음으로 사용하는 것.
	본인의 기능을 본인만 사용하게 한다.
*/

// 3. 추상화 - 특정되지 않고 포괄적이다.(보편적이고 일반화된 특징들을 추출)
/*
	존재하지 않는 형태를 추상 클래스라고 한다.
	예) 사람, 학생, 군인 등의 대상이 특정되지 않는 경우(추상적인 경우)
	예) "홍길동은 학생이다." 라면 홍길동이라는 특정 대상이 있으므로, 추상적 형태로 볼 수 없음.
*/

// 4. 상속 - 부모 개체가 가진 걸 자식 개체가 사용할 수 있다.
/*
	자식 클래스는 부모 클래스꺼를 사용할 수 있다.(코드의 재사용이 용이)
	다만 자식 클래스에 변수가 있을 경우 자식 클래스에 있는 변수가 사용된다.
	부모 클래스에 있는걸 자식 클래스에서 또 만드는 실수를 많이할 수 있으니 주의.
*/

// 5. 다형성 - 특정 범주에서 형태가 달라도 상관없다.
/*
	다양한 형태로 존재할 수 있다.
	부모 타입의 포인터 딱 하나로 여러 자식들의 멤버를 호출할 수 있는 것
*/

// 6. namespace - 별도의 영역을 지정하여 동일한 이름의 함수를 사용할 수 있도록 함.
/*
namespace AAA
{
	void Output()
	{
		cout << "홍길동" << endl;
	}
}

namespace BBB
{
	void Output()
	{
		cout << "임꺽정" << endl;
	}
}

using AAA::Output;
*/

// 7. 생성자 & 소멸자 & 복사 생성자

/*
struct tagInfo
{
	int Number;
};

class Object
{
private:
protected:
	tagInfo m_Info;
public:
	int Number;
	char* Name;
public:
	virtual Object* Clone() = 0;
public:
	// 사용자가 호출하지 않아도 스스로 호출됨.
	// 클래스가 생성된 직후 호출
	Object()
	{
		cout << "생성자" << endl;
	};

	// 사용자가 호출하는 시점에 호출됨.
	// 전달값의 개수와 자료형에 따라서 선택적(자동)으로 호출됨.
	Object(int _Number) : Number(_Number)
	{
		cout << "복사 생성자 : int" << endl;

		//Number = _Number;
	};
	Object(float _Number)
	{
		cout << "복사 생성자 : float" << endl;

		Number = (int)_Number;
	};

	Object(char* _Name)
	{
		Name = new char[strlen(_Name) + 1];
		strcpy(Name, _Name);
	};

	// 클래스가 삭제되기 직전
	~Object()
	{
		cout << "소멸자" << endl;

		delete Name;
		//Name = nullptr;
	};

	Object(Object* _obj)
	{
		Name = new char[strlen(_obj->Name) + 1];
		strcpy(Name, _obj->Name);
	};

	Object(tagInfo _Info) : m_Info(_Info)
	{

	}
};

class Player : public Object
{
public:
	virtual Object* Clone() override { return new Player(*this); }

	void Output() { cout << m_Info.Number << endl; }

public:
	Player() {};

	Player(tagInfo _Info) : Object(_Info) {};
	~Player() {};
};
*/

//map<string, Object*> PrototypeObject;
//
//Object* GetObject(string _Key);

// 8. 깊은 복사, 얕은 복사
/*
	얕은 복사(Shallow Copy)는 '주소 값'을 복사하기 때문에 참조하고 있는 실제값은 같다.
	깊은 복사(Deep Copy)는 '실제 값'을 새로운 메모리 공간에 복사하는 것이다.
	복사할때 주소만 복사된 경우에는 안에 있는 값도 복사가 가능하도록 새롭게 동적할당을 해주어야한다.
*/

// 9. 오버로딩 & 오버라이딩 - 어떻게 호출할 것인지가 핵심
/*
	오버로딩은 복사생성자와 같은 형태로 사용가능하고, 매개변수가 다를 경우 다른 기능을 한다.
	이름은 같지만 시그니처(파라미터 수, 타입)에는 다른 메서드를 중복 선언하는 것을 의미한다.

	오버라이딩은 상속의 범위에 포함되며, 파생클래스에서 사용이 가능하다. 그리고 오버로딩된 개체를 오버라이딩할 수 있다.
	부모 클래스의 메서드의 동작 방법을 재정의하여 사용하는 것을 의미한다.

	※ 오버로딩은 리턴 타입이 무엇이든지 상관없이 매개변수나 타입이 달라야하지만 오버라이딩은 동일해야한다. 
*/

/*
class Object
{
public:
	virtual void Output()
	{
		cout << "Object : " << endl;
	}

	void Output(string _str)
	{
		cout << "Object : " << _str << endl;
	}
};

class AAA : public Object
{
public:
	void Output() override
	{
		cout << "AAA : " << endl;
	}

	void Output(string _str)
	{
		cout << "AAA : " << _str << endl;
	}
};
*/

// 10. 연산자 오버로딩 - 연산자에 임의로 설정한 기능을 가능하도록 하는 것
struct tagInfo
{
	int Number;

	tagInfo() {};
	tagInfo(int _Number) : Number(_Number) {};
};

class Object
{
private:
	tagInfo Info;
public:
	Object& operator+=(const Object& _Obj)
	{
		Info.Number += _Obj.Info.Number;
		return *this;
	}

	Object& operator++()
	{
		Info.Number += 1;
		return *this;
	}

	Object& operator--()
	{
		Info.Number -= 1;
		return *this;
	}

	void Output()
	{
		cout << Info.Number << endl;
	}
public:
	Object() {}
	Object(tagInfo _Info) : Info(_Info) {}
	~Object() {}
};

// 11. 포인터 (복습) & 캡슐화

int main(void)
{
	/*
	Object o1((char*)"홍길동");
	o1.Number = 10;
	Object o2(o1);
	o1.Name = (char*)"임꺽정";

	cout << o2.Number << endl;
	cout << o1.Name << endl;
	cout << o2.Name << endl;
	*/

	/*
	tagInfo Info;
	Info.Number = 10;

	AAA a[8];

	for (int i = 0; i < 8; ++i)
	{
		Info.Number = i;
		a[i] = AAA(Info);
	}

	for (int i = 0; i < 8; ++i)
		a[i].Output();
	*/

	/*
	tagInfo Info;

	Info.Number = 10;
	PrototypeObject["Player"] = new Player(); // Player를 동적할당함

	Object* pProtoObj = GetObject("Player"); // 오브젝트 포인터에 GetObject로 생성해준다.

	Object* pPlayer = nullptr;

	if (pProtoObj != nullptr)
		pPlayer = pProtoObj->Clone();
	*/

	Object o1(tagInfo(10));
	Object o2(o1);

	o2 += o1;
	++o2;
	o2.Output();

	return 0;
}
/*
Object* GetObject(string _Key)
{
	map<string, Object*>::iterator iter = PrototypeObject.find(_Key);

	if (iter == PrototypeObject.end())
		return nullptr;
	else
		return iter->second;
}
*/