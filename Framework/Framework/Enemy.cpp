#include "Enemy.h"
#include "EnemyBullet.h"
#include "CursorManager.h"
#include "ObjectManager.h"
#include "NormalEnemyBullet.h"

#define PI 3.141592f

Enemy::Enemy() { }

Enemy::Enemy(Transform _TransInfo) : Object(_TransInfo) {}

Enemy::~Enemy() { }

Object* Enemy::Initialize(string _Key)
{
	strKey = _Key;

	Buffer[0] = (char*)"  ¡ã";
	Buffer[1] = (char*)"  ¡á  ¡ã";
	Buffer[2] = (char*)"¡Ü¡á¡á¡á";
	Buffer[3] = (char*)"  ¡á  ¡å";
	Buffer[4] = (char*)"  ¡å";

	TransInfo.Position = Vector3(0.0f, 0.0f);
	TransInfo.Rotation = Vector3(0.0f, 0.0f);
	TransInfo.Scale = Vector3(10.0f, 5.0f);

	return this;
}

int Enemy::Update()
{
	TransInfo.Position.x -= 1.25f;

	int time = rand() % 200;
	
	if (time == 5)
	{
		Bridge* pBridge = new NormalEnemyBullet;
		ObjectManager::GetInstance()->AddObject("EnemyBullet", pBridge, TransInfo.Position);
	}
	//else if (time == 6)
	//	TransInfo.Position.y += 1.8f;

	return 0;
}

void Enemy::Render()
{
	for (int i = 0; i < 5; ++i)
	{
		CursorManager::GetInstance()->WriteBuffer(
			TransInfo.Position.x,
			TransInfo.Position.y - (TransInfo.Scale.y * 0.5f) + i,
			Buffer[i], 15);
	}
}

void Enemy::Release()
{

}