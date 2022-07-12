#include "Enemy.h"
#include "CursorManager.h"
#include "ObjectPool.h"

Enemy::Enemy() { }

Enemy::Enemy(Transform _TransInfo) : Object(_TransInfo) {}

Enemy::~Enemy() { }

Object* Enemy::Initialize(string _Key)
{
	strKey = _Key;

	Buffer[0] = (char*)"È£";
	Buffer[1] = (char*)"¤µ";

	TransInfo.Position = Vector3(0.0f, 0.0f);
	TransInfo.Rotation = Vector3(0.0f, 0.0f);
	TransInfo.Scale = Vector3(float(strlen(Buffer[0])), (float)MAX_SIZE);

	return this;
}

int Enemy::Update()
{
	TransInfo.Position.x -= 1.25f;

	return 0;
}

void Enemy::Render()
{
	for (int i = 0; i < MAX_SIZE; ++i)
	{
		CursorManager::GetInstance()->WriteBuffer(
			TransInfo.Position.x,
			TransInfo.Position.y + i,
			Buffer[i]);
	}
}

void Enemy::Release()
{

}