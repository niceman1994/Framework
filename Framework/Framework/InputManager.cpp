#include "InputManager.h"

InputManager* InputManager::Instance = nullptr;

InputManager::InputManager() : Key(0), Pressed(false) {}

InputManager::~InputManager() {}

void InputManager::InputKey()
{
	Key = 0;
	Pressed = false;
	
	if (GetAsyncKeyState(VK_UP))
		Key |= KEY_UP;

	if (GetAsyncKeyState(VK_DOWN))
		Key |= KEY_DOWN;

	if (GetAsyncKeyState(VK_LEFT))
		Key |= KEY_LEFT;

	if (GetAsyncKeyState(VK_RIGHT))
		Key |= KEY_RIGHT;

	if (GetAsyncKeyState(VK_SPACE))
		Key |= KEY_SPACE;

	if (GetAsyncKeyState(VK_RETURN))
		Key |= KEY_ENTER;

	if (GetAsyncKeyState(VK_CONTROL))
		Key |= KEY_CTRL;

	if (GetAsyncKeyState(VK_MENU))
		Key |= KEY_ALT;

	if (GetAsyncKeyState(VK_TAB))
		Key |= KEY_TAB;

	if (GetAsyncKeyState(VK_ESCAPE))
		Key |= KEY_ESCAPE;

	if (GetAsyncKeyState(VK_CANCEL))
		Key |= KEY_CANCEL;

	if (GetAsyncKeyState(0x30))
		Key |= PRESS_0;

	if (GetAsyncKeyState(0x31))
		Key |= PRESS_1;

	if (GetAsyncKeyState(0x32))
		Key |= PRESS_2;

	if (GetAsyncKeyState(0x33))
		Key |= PRESS_3;
}