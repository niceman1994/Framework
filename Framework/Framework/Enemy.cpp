#include "Enemy.h"
//#include "ObjectManager.h"
//#include "CursorManager.h"
//#include "NormalEnemyBullet.h"
#include "Bridge.h"

Enemy::Enemy() { }

Enemy::Enemy(Transform _TransInfo) : Object(_TransInfo) {}

Enemy::~Enemy() { }

Object* Enemy::Initialize(string _Key)
{
	strKey = _Key;

	Buffer[0] = (char*)"  ¡ã    ";
	Buffer[1] = (char*)"  ¡á  ¡ã";
	Buffer[2] = (char*)"¡Ü¡á¡á¡á";
	Buffer[3] = (char*)"  ¡á  ¡å";
	Buffer[4] = (char*)"  ¡å    ";

	//Buffer[0] = (char*)"";
	//Buffer[1] = (char*)"";
	//Buffer[2] = (char*)"";
	//Buffer[3] = (char*)"";
	//Buffer[4] = (char*)"";

	TransInfo.Position = Vector3(0.0f, 0.0f);
	TransInfo.Rotation = Vector3(0.0f, 0.0f);
	TransInfo.Scale = Vector3(10.0f, 5.0f);

	TransInfo.Direction = Vector3(0.0f, 0.0f);

	if (pBridge)
		pBridge->Initialize();

	return this;
}

int Enemy::Update()
{
	//TransInfo.Position.x -= 1.5f;
	//
	//if (TransInfo.Position.x <= 178.0f && pBridge->GetBridgeKey() == "FlyingEnemy")
	//{
	//	if (rand() % 100 == 5)
	//	{
	//		Bridge* pBridge = new NormalEnemyBullet;
	//		ObjectManager::GetInstance()->AddObject("EnemyBullet", pBridge, TransInfo.Position);
	//	}
	//}

	if (pBridge)
		pBridge->Update(TransInfo);

	return 0;
}

void Enemy::Render()
{
	//for (int i = 0; i < 5; ++i)
	//{
	//	CursorManager::GetInstance()->WriteBuffer(
	//		TransInfo.Position.x,
	//		TransInfo.Position.y - (TransInfo.Scale.y * 0.5f) + i,
	//		Buffer[i], 15);
	//}

	if (pBridge)
		pBridge->Render();
}

void Enemy::Release()
{
	delete pBridge;
	pBridge = nullptr;
}