#include "Player.h"
#include "InputManager.h"
#include "CursorManager.h"
#include "Bullet.h"
#include "ObjectManager.h"
#include "ObjectFactory.h"
#include "NormalBullet.h"

Player::Player() { }
Player::Player(Transform _TransInfo) : Object(_TransInfo) { }
Player::~Player() { }


Object* Player::Initialize(string _Key)
{
	strKey = _Key;

	//Buffer[0] = (char*)"｜＼   ｜＼ ";
	//Buffer[1] = (char*)" ＼ ￣￣  ￣￣＼";
	//Buffer[2] = (char*)"   ￣￣￣￣￣￣";

	Buffer[0] = (char*)"오";
	Buffer[1] = (char*)"ㅅ";

	//TransInfo.Position = Vector3(20.0f, 15.0f);
	//TransInfo.Rotation = Vector3(0.0f, 0.0f);
	//TransInfo.Scale = Vector3(17.0f, 3.0f);

	TransInfo.Position = Vector3(20.0f, 15.0f);
	TransInfo.Rotation = Vector3(0.0f, 0.0f);
	TransInfo.Scale = Vector3(2.0f, 2.0f);

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
		ObjectManager::GetInstance()->AddObject(
			CreateBullet<NormalBullet>());
	}

	/*
	if (dwKey & KEY_SPACE)
	{
		CreateBullet<(다른거)NormalBullet>();
	}
	*/

	return 0;
}

void Player::Render()
{
	//for (int i = 0; i < 3; ++i)
	//{
	//	CursorManager::GetInstance()->WriteBuffer(
	//		TransInfo.Position.x,
	//		TransInfo.Position.y - (TransInfo.Scale.y * 0.5f) + i,
	//		Buffer[i], Color);
	//}

	for (int i = 0; i < MAX_SIZE; ++i)
	{
		CursorManager::GetInstance()->WriteBuffer(
			TransInfo.Position.x - (TransInfo.Scale.x * 0.5f),
			TransInfo.Position.y - (TransInfo.Scale.y * 0.5f) + i,
			Buffer[i]);
	}
}

void Player::Release()
{

}

template<typename T>
Object* Player::CreateBullet()
{
	Bridge* pBridge = new T;
	Object* pBullet = ObjectFactory<Bullet>::CreateObject(TransInfo.Position, pBridge); // 총알에 속성(pBridge)을 주고난 후 반환

	return pBullet;
}
