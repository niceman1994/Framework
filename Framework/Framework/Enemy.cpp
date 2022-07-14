#include "Enemy.h"
#include "Bullet.h"
#include "EnemyBullet.h"
#include "CursorManager.h"
#include "ObjectPool.h"
#include "ObjectManager.h"
#include "ObjectFactory.h"
#include "InputManager.h"

Enemy::Enemy() { }

Enemy::Enemy(Transform _TransInfo) : Object(_TransInfo) {}

Enemy::~Enemy() { }

Object* Enemy::Initialize(string _Key)
{
	strKey = _Key;

	Buffer[0] = (char*)"  ¡â";
	Buffer[1] = (char*)"  ¡à  ¡â";
	Buffer[2] = (char*)"¡Ü¡à¡à¡à";
	Buffer[3] = (char*)"  ¡à  ¡ä";
	Buffer[4] = (char*)"  ¡ä";

	TransInfo.Position = Vector3(0.0f, 0.0f);
	TransInfo.Rotation = Vector3(0.0f, 0.0f);
	TransInfo.Scale = Vector3(10.0f, 5.0f);

	return this;
}

int Enemy::Update()
{
	TransInfo.Position.x -= 1.25f;

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