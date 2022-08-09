#include "SpecialSkill.h"
#include "ObjectManager.h"
#include "CursorManager.h"
#include "MathManager.h"

SpecialSkill::SpecialSkill() {}

SpecialSkill::~SpecialSkill() {}

void SpecialSkill::Initialize()
{
	BridgeKey = "SpecialSkill";

	Speed = -3.0f;
	Color = 15;
}

int SpecialSkill::Update(Transform& Info)
{
	Info.Direction = MathManager::GetDirection(
		Info.Position, Vector3(0.0f, Info.Position.y));

	Info.Position -= Info.Direction * Speed;

	return 0;
}

void SpecialSkill::Render()
{
	CursorManager::GetInstance()->WriteBuffer(
		pObject->GetPosition().x + (pObject->GetScale().x),
		pObject->GetPosition().y - pObject->GetScale().y * 0.33f,
		(char*)"", Color);
}

void SpecialSkill::Release()
{
}
