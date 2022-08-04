#include "FlyingEnemy.h"
#include "MathManager.h"
#include "CursorManager.h"
#include "ObjectManager.h"
#include "NormalEnemyBullet.h"

FlyingEnemy::FlyingEnemy() {}

FlyingEnemy::~FlyingEnemy() {}

void FlyingEnemy::Initialize()
{
	BridgeKey = "FlyingEnemy";

	ObjectText[0] = (char*)"  ¡ã    ";
	ObjectText[1] = (char*)"  ¡á  ¡ã";
	ObjectText[2] = (char*)"¡Ü¡á¡á¡á";
	ObjectText[3] = (char*)"  ¡á  ¡å";
	ObjectText[4] = (char*)"  ¡å    ";

	Speed = -1.1f;
	Color = 15;
}

int FlyingEnemy::Update(Transform& Info)
{
	Info.Direction = MathManager::GetDirection(
		Info.Position, Vector3(0.0f, Info.Position.y));
	
	Info.Position -= Info.Direction * Speed;

	if (Info.Position.x <= 178.0f)
	{
		if (rand() % 10 == 5)
		{
			Bridge* pBridge = new NormalEnemyBullet;
			ObjectManager::GetInstance()->AddObject("EnemyBullet", pBridge, Info.Position);
		}
	}

	return 0;
}

void FlyingEnemy::Render()
{
	for (int i = 0; i < 5; ++i)
	{
		CursorManager::GetInstance()->WriteBuffer(
			pObject->GetPosition().x,
			pObject->GetPosition().y - (pObject->GetScale().y * 0.5f) + i,
			ObjectText[i], Color);
	}
}

void FlyingEnemy::Release()
{
}
