#include "LifeUpItem.h"
#include "MathManager.h"
#include "CursorManager.h"

LifeUpItem::LifeUpItem() {}

LifeUpItem::~LifeUpItem() {}

void LifeUpItem::Initialize()
{
    BridgeKey = "LifeUpItem";

    ItemText[0] = (char*)"¦£¦¡¦¤";
    ItemText[1] = (char*)"¦¢£Õ¦¢";
    ItemText[2] = (char*)"¦¦¦¡¦¥";

    Speed = -0.7f;
    Color = 11;
}

int LifeUpItem::Update(Transform& Info)
{
    Info.Direction = MathManager::GetDirection(
        Info.Position, Vector3(0.0f, Info.Position.y));

    Info.Position -= Info.Direction * Speed;

	return 0;
}

void LifeUpItem::Render()
{
    for (int i = 0; i < 3; ++i)
    {
        CursorManager::GetInstance()->WriteBuffer(
            pObject->GetPosition().x,
            pObject->GetPosition().y - (pObject->GetScale().y * 0.5f) + i,
            ItemText[i], Color);
    }
}

void LifeUpItem::Release()
{
}
