#include "Enemy.h"
#include "CursorManager.h"

Enemy::Enemy() { }

Enemy::Enemy(Transform _TransInfo) : Object(_TransInfo) {}

Enemy::~Enemy() { }

void Enemy::Initialize()
{
	strKey = "��";

	TransInfo.Position = Vector3(0.0f, 0.0f);
	TransInfo.Rotation = Vector3(0.0f, 0.0f);
	TransInfo.Scale = Vector3(2.0f, 1.0f);
}

int Enemy::Update()
{
	TransInfo.Position.x -= 2;

	if (TransInfo.Position.x <= 0)
		return 1;

	return 0;
}

void Enemy::Render()
{
	CursorManager::Draw(
		TransInfo.Position.x,
		TransInfo.Position.y, 
		strKey);
}

void Enemy::Release()
{
}