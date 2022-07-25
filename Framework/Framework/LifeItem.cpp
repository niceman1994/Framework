#include "LifeItem.h"
#include "MathManager.h"
#include "CursorManager.h"
#include "ObjectManager.h"

LifeItem::LifeItem() {}

LifeItem::~LifeItem() {}

void LifeItem::Initialize()
{
    BridgeKey = "LifeItem";

    ItemText[0] = (char*)"¦£¦¡¦¤";
    ItemText[1] = (char*)"¦¢£Ì¦¢";
    ItemText[2] = (char*)"¦¦¦¡¦¥";

    Speed = -0.7f;
    Color = 14;
}

int LifeItem::Update(Transform& Info)
{
    Info.Direction = MathManager::GetDirection(
        Info.Position, Vector3(0.0f, Info.Position.y));

    Info.Position -= Info.Direction * Speed;

    return 0;
}

void LifeItem::Render()
{
    for (int i = 0; i < 3; ++i)
    {
        CursorManager::GetInstance()->WriteBuffer(
            pObject->GetPosition().x,
            pObject->GetPosition().y - (pObject->GetScale().y * 0.5f) + i,
            ItemText[i], Color);
    }
}

void LifeItem::Release()
{
}
