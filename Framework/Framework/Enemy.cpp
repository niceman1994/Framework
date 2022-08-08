#include "Enemy.h"
#include "Bridge.h"

Enemy::Enemy() { }

Enemy::Enemy(Transform _TransInfo) : Object(_TransInfo) {}

Enemy::~Enemy() { }

Object* Enemy::Initialize(string _Key)
{
	strKey = _Key;

	//Buffer[0] = (char*)"  ¡ã    ";
	//Buffer[1] = (char*)"  ¡á  ¡ã";
	//Buffer[2] = (char*)"¡Ü¡á¡á¡á";
	//Buffer[3] = (char*)"  ¡á  ¡å";
	//Buffer[4] = (char*)"  ¡å    ";

	TransInfo.Position = Vector3(0.0f, 0.0f);
	TransInfo.Rotation = Vector3(0.0f, 0.0f);
	TransInfo.Scale = Vector3(8.0f, 5.0f);

	TransInfo.Direction = Vector3(0.0f, 0.0f);

	if (pBridge)
		pBridge->Initialize();

	return this;
}

int Enemy::Update()
{
	if (pBridge)
		pBridge->Update(TransInfo);

	return 0;
}

void Enemy::Render()
{
	if (pBridge)
		pBridge->Render();
}

void Enemy::Release()
{
	delete pBridge;
	pBridge = nullptr;
}