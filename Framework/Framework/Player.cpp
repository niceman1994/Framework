#include "Player.h"
#include "InputManager.h"
#include "CursorManager.h"
#include "Bullet.h"
#include "ObjectManager.h"
#include "ScoreManager.h"
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

	Buffer[0] = (char*)"    ¡â";
	Buffer[1] = (char*)"¡â  ¡à";
	Buffer[2] = (char*)"¡à¡à¡à¢º";
	Buffer[3] = (char*)"¡ä  ¡à";
	Buffer[4] = (char*)"    ¡ä";

	TransInfo.Position = Vector3(20.0f, 15.0f);
	TransInfo.Rotation = Vector3(0.0f, 0.0f);
	TransInfo.Scale = Vector3(10.0f, 5.0f);

	return this;
}

int Player::Update()
{
	DWORD dwKey = InputManager::GetInstance()->GetKey();

	if (dwKey & KEY_UP)
	{
		TransInfo.Position.y -= 1.0f;

		if (TransInfo.Position.y <= 5.0f)
			TransInfo.Position = Vector3(TransInfo.Position.x, 5.0f); 
	}

	if (dwKey & KEY_DOWN)
	{
		TransInfo.Position.y += 1.0f;

		if (TransInfo.Position.y >= 46.0f)
			TransInfo.Position = Vector3(TransInfo.Position.x, 46.0f);
	}

	if (dwKey & KEY_LEFT)
	{
		TransInfo.Position.x -= 1.0f;

		if (TransInfo.Position.x <= 0.0f)
			TransInfo.Position = Vector3(2.0f, TransInfo.Position.y);
	}

	if (dwKey & KEY_RIGHT)
	{
		TransInfo.Position.x += 1.0f;

		if (TransInfo.Position.x >= 170.0f)
			TransInfo.Position = Vector3(170.0f, TransInfo.Position.y);
	}	

	if (dwKey & KEY_SPACE && ScoreManager::GetInstance()->GetStageScore() < 5000)
	{
		Bridge* pBridge = new NormalBullet;
		ObjectManager::GetInstance()->AddObject("Bullet", pBridge, TransInfo.Position);
	}

	if (dwKey & KEY_SPACE && ScoreManager::GetInstance()->GetStageScore() >= 5000)
	{
		Bridge* pBridge = new TwinBullet;
		ObjectManager::GetInstance()->AddObject("Bullet", pBridge, TransInfo.Position);
	}

	if (dwKey & KEY_CTRL)
	{
		
	}

	return 0;
}

void Player::Render()
{
	//CursorManager::GetInstance()->WriteBuffer(0.0f, 1.0f, (char*)"X : ");
	//CursorManager::GetInstance()->WriteBuffer(0.0f, 2.0f, (char*)"Y : ");
	//CursorManager::GetInstance()->WriteBuffer(0.0f, 3.0f, (char*)"R : ");
	//CursorManager::GetInstance()->WriteBuffer(4.0f, 1.0f, (int)TransInfo.Position.x);
	//CursorManager::GetInstance()->WriteBuffer(4.0f, 2.0f, (int)TransInfo.Position.y);
	//CursorManager::GetInstance()->WriteBuffer(4.0f, 3.0f, (int)TransInfo.Rotation.x);

	for (int i = 0; i < 5; ++i)
	{
		CursorManager::GetInstance()->WriteBuffer(
			TransInfo.Position.x,
			TransInfo.Position.y - (TransInfo.Scale.y * 0.5f) + i,
			Buffer[i], 15);
	}
}

void Player::Release()
{

}
