#include "RushingEnemy.h"
#include "MathManager.h"
#include "CursorManager.h"
#include "ObjectManager.h"

RushingEnemy::RushingEnemy() {}

RushingEnemy::~RushingEnemy() {}

void RushingEnemy::Initialize()
{
	BridgeKey = "RushingEnemy";

	ObjectText[0] = (char*)"  ��������";
	ObjectText[1] = (char*)" ��     ��";
	ObjectText[2] = (char*)"��      ��";
	ObjectText[3] = (char*)" ��     ��";
	ObjectText[4] = (char*)"  ��������";

	Speed = 1.5f;
	Color = 15;
}

int RushingEnemy::Update(Transform& Info)
{
	Info.Direction = MathManager::GetDirection(
		Info.Position, Vector3(90.0f, Info.Position.y));
	
	if (Info.Position.x == 90.0f)
	{
		Info.Direction = MathManager::GetDirection(
			Info.Position, Vector3(100.0f, Info.Position.y + 10.0f));
	}
	else if (Info.Position.x == 100.0f)
	{
		Info.Direction = MathManager::GetDirection(
			Info.Position, Vector3(90.0f, Info.Position.y - 10.0f));
	}

	Info.Position += Info.Direction * Speed;

    return 0;
}

void RushingEnemy::Render()
{
	for (int i = 0; i < 5; ++i)
	{
		CursorManager::GetInstance()->WriteBuffer(
			pObject->GetPosition().x,
			pObject->GetPosition().y - (pObject->GetScale().y * 0.5f) + i,
			ObjectText[i], Color);
	}
}

void RushingEnemy::Release()
{
}