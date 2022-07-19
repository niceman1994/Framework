#include "PowerUpItem.h"
#include "MathManager.h"
#include "CursorManager.h"
#include "ObjectManager.h"

PowerUpItem::PowerUpItem() {}

PowerUpItem::~PowerUpItem() {}

void PowerUpItem::Initialize()
{
	Color = 13;
	Speed = 0.8f;
}

int PowerUpItem::Update(Transform& Info)
{
	Info.Direction = MathManager::GetDirection(
		Info.Position, Vector3(1.0f, Info.Position.y));

	return 0;
}

void PowerUpItem::Render()
{
    if (pObject->GetPosition().x >= 2.0f)
    {
        for (int i = 0; i < 3; ++i)
        {
            CursorManager::GetInstance()->WriteBuffer(
                pObject->GetPosition().x,
                pObject->GetPosition().y - (pObject->GetScale().y * 0.5f) + i,
                (char*)
                "¦£¦¡¦¤"
                "¦¢£Ð¦¢"
                "¦¦¦¡¦¥"
                , Color);
        }
    }
}

void PowerUpItem::Release()
{
}
