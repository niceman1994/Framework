#include "NormalBullet.h"
#include "CursorManager.h"
#include "MathManager.h"
#include "Object.h"

NormalBullet::NormalBullet()
{
}

NormalBullet::~NormalBullet()
{
}

void NormalBullet::Initialize()
{
	// Bullet의 데이터 초기화
	Speed = 0.5f;
	Color = 12;
}

int NormalBullet::Update(Transform& Info)
{
	//Info.Direction = MathManager::GetDirection(
	//	Info.Position, Vector3(60.0f, 15.0f));

	Info.Direction = MathManager::GetDirection(
		Info.Position, Vector3(120.0f, Info.Position.y));

	Info.Position += Info.Direction * Speed;

	return 0;
}

void NormalBullet::Render()
{
	CursorManager::GetInstance()->WriteBuffer(
		pObject->GetPosition().x + 0.5f,
		pObject->GetPosition().y,
		(char*)"＊", Color);
}

void NormalBullet::Release()
{
}
