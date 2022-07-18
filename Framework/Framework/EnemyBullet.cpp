#include "EnemyBullet.h"
#include "Bridge.h"

EnemyBullet::EnemyBullet() {}

EnemyBullet::EnemyBullet(Transform _TransInfo) : Object(_TransInfo) {}

EnemyBullet::~EnemyBullet() { Release(); }

Object* EnemyBullet::Initialize(string _Key)
{
	strKey = _Key;

	Buffer[0] = (char*)"£ª";

	TransInfo.Position = Vector3(0.0f, 0.0f);
	TransInfo.Rotation = Vector3(0.0f, 0.0f);
	TransInfo.Scale = Vector3(2.0f, 2.0f);

	TransInfo.Direction = Vector3(0.0f, 0.0f);

	if (pBridge)
		pBridge->Initialize();

	return this;
}

int EnemyBullet::Update()
{
	if (pBridge)
		pBridge->Update(TransInfo);

	return 0;
}

void EnemyBullet::Render()
{
	if (pBridge)
		pBridge->Render();
}

void EnemyBullet::Release()
{
	delete pBridge;
	pBridge = nullptr;
}

