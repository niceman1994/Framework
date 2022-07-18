#include "NormalBullet.h"
#include "ObjectManager.h"
#include "CursorManager.h"
#include "MathManager.h"
#include "Object.h"

NormalBullet::NormalBullet() {}

NormalBullet::~NormalBullet() {}

void NormalBullet::Initialize()
{
	Speed = 1.2f;
	Color = 12;
}

int NormalBullet::Update(Transform& Info)
{
	

	Info.Direction = MathManager::GetDirection(
		Info.Position, Vector3(180.0f, Info.Position.y));

	Info.Position += Info.Direction * Speed;

	return 0;
}

void NormalBullet::Render()
{
	CursorManager::GetInstance()->WriteBuffer(
		pObject->GetPosition().x + (pObject->GetScale().x),
		pObject->GetPosition().y - pObject->GetScale().y * 0.33f,
		(char*)"£ª", Color);
}

void NormalBullet::Release()
{
}
