#include "ScoreItem.h"
#include "MathManager.h"
#include "CursorManager.h"
#include "ObjectManager.h"

ScoreItem::ScoreItem()
{
}

ScoreItem::~ScoreItem()
{
}

void ScoreItem::Initialize()
{
    BridgeKey = "ScoreItem";

    ItemText[0] = (char*)"¦£¦¡¦¤";
    ItemText[1] = (char*)"¦¢£Ó¦¢";
    ItemText[2] = (char*)"¦¦¦¡¦¥";

    Speed = -0.7f;
    Color = 13;
}

int ScoreItem::Update(Transform& Info)
{
    Info.Direction = MathManager::GetDirection(
        Info.Position, Vector3(0.0f, Info.Position.y));

    Info.Position -= Info.Direction * Speed;

    return 0;
}

void ScoreItem::Render()
{
    for (int i = 0; i < 3; ++i)
    {
        CursorManager::GetInstance()->WriteBuffer(
            pObject->GetPosition().x,
            pObject->GetPosition().y - (pObject->GetScale().y * 0.5f) + i,
            ItemText[i], Color);
    }
}

void ScoreItem::Release()
{
}
