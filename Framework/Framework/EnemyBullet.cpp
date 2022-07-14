#include "EnemyBullet.h"
#include "CursorManager.h"
#include "MathManager.h"

EnemyBullet::EnemyBullet() {}

EnemyBullet::EnemyBullet(Transform _TransInfo) : Object(_TransInfo) {}

EnemyBullet::~EnemyBullet() {}

Object* EnemyBullet::Initialize(string _Key)
{
	strKey = _Key;

	Buffer[0] = (char*)"£ª";

	TransInfo.Position = Vector3(0.0f, 0.0f);
	TransInfo.Rotation = Vector3(0.0f, 0.0f);
	TransInfo.Scale = Vector3(2.0f, 2.0f);

	TransInfo.Direction = Vector3(0.0f, 0.0f);

	return this;
}

int EnemyBullet::Update()
{
	TransInfo.Position.x -= 1.55f;

	return 0;
}

void EnemyBullet::Render()
{
	CursorManager::GetInstance()->WriteBuffer(TransInfo.Position, Buffer[0]);
}

void EnemyBullet::Release()
{
}

