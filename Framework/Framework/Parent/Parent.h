#pragma once
#include "Headers.h"

class Parent
{
private:
	// 자기 자신만 사용 가능.

protected:
	// 상속간의 공개된 상태. 비상속 클레스 사용불가. 외부 사용 불가.
	int m_Number;
public:
	// 공개된 상태
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Output() = 0;

	// [virtual] = 가상함수
	// [= 0] : virtual 함수에만 붙일수 있다.
	// 함수의 끝에 [= 0] 붙이게 되면 [순수 가상 함수] 가 된다.

	// [순수 가상 함수]
	// virtual 함수가 함수의 몸체(정의)가 없을때 사용한다.

	// virtual 함수를 사용하는 이유?
	// 형변환을 일일히 지정하기에는 효율적이지 않기때문이다.
	// virtual 함수는 추상 클래스라 함수의 정의를 할 수 없다.
};