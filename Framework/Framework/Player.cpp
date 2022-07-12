#include "Player.h"
#include "InputManager.h"
#include "CursorManager.h"
#include "Bullet.h"
#include "ObjectManager.h"
#include "ObjectFactory.h"
#include "Prototype.h"
#include "NormalBullet.h"
#include "TwinBullet.h"

Player::Player() { }
Player::Player(Transform _TransInfo) : Object(_TransInfo) { }
Player::~Player() { }

Object* Player::Initialize(string _Key)
{
	strKey = _Key;

	Buffer[0] = (char*)"£ü¡¬£ß£ü¡¬£ß ";
	Buffer[1] = (char*)" ¡¬£ß£ß£ß£ß¡¦¡¬";

	//Buffer[0] = (char*)"¿À";
	//Buffer[1] = (char*)"¤µ";

	TransInfo.Position = Vector3(20.0f, 15.0f);
	TransInfo.Rotation = Vector3(0.0f, 0.0f);
	TransInfo.Scale = Vector3(16.0f, 2.0f);

	//TransInfo.Position = Vector3(20.0f, 15.0f);
	//TransInfo.Rotation = Vector3(0.0f, 0.0f);
	//TransInfo.Scale = Vector3(2.0f, 2.0f);

	return this;
}

int Player::Update()
{
	DWORD dwKey = InputManager::GetInstance()->GetKey();

	if (dwKey & KEY_UP)
		TransInfo.Position.y -= 1;

	if (dwKey & KEY_DOWN)
		TransInfo.Position.y += 1;

	if (dwKey & KEY_LEFT)
		TransInfo.Position.x -= 1;

	if (dwKey & KEY_RIGHT)
		TransInfo.Position.x += 1;

	if (dwKey & KEY_SPACE)
	{
		Bridge* pBridge = new NormalBullet;
		ObjectManager::GetInstance()->AddObject("Bullet", pBridge, TransInfo.Position);
	}

	if (dwKey & KEY_CTRL)
	{
		Bridge* pBridge = new TwinBullet;
		ObjectManager::GetInstance()->AddObject("Bullet", pBridge, TransInfo.Position);
	}

	return 0;
}

void Player::Render()
{
	for (int i = 0; i < 2; ++i)
	{
		CursorManager::GetInstance()->WriteBuffer(
			TransInfo.Position.x,
			TransInfo.Position.y - (TransInfo.Scale.y * 0.5f) + i,
			Buffer[i], 15);
	}

	//for (int i = 0; i < MAX_SIZE; ++i)
	//{
	//	CursorManager::GetInstance()->WriteBuffer(
	//		TransInfo.Position.x,
	//		TransInfo.Position.y + i,
	//		Buffer[i], 15);
	//}
}

void Player::Release()
{

}
