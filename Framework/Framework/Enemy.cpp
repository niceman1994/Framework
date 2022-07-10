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

	Color = 15;

	return this;
}

int Enemy::Update()
{
	//TransInfo.Position.x -= 1.1f;

	if (TransInfo.Position.x <= 0)
		return BUFFER_OVER;

	return 0;
}

void Enemy::Render()
{
	for (int i = 0; i < MAX_SIZE; ++i)
	{
		CursorManager::GetInstance()->WriteBuffer(
			TransInfo.Position.x - (TransInfo.Scale.x * 0.5f),
			TransInfo.Position.y - (TransInfo.Scale.y * 0.5f) + i,
			Buffer[i], Color);
	}
}

void Enemy::Release()
{

}