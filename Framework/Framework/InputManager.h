#pragma once
#include "Headers.h"

class InputManager
{
private:
	static InputManager* Instance;
public:
	static InputManager* GetInstance()
	{
		if (Instance == nullptr)
			Instance = new InputManager;

		return Instance;
	}
private:
	DWORD Key;
	bool Pressed;
public:
	DWORD GetKey() const { return Key; } // const는 값을 건드리지 말라는 의미, 변경이 불가능해서 대입이 불가능
public:
	void InputKey();
private:
	InputManager();
public:
	~InputManager();
};