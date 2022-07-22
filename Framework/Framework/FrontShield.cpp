#include "FrontShield.h"
#include "CursorManager.h"
#include "ObjectManager.h"
#include "MathManager.h"

FrontShield::FrontShield() {}

FrontShield::FrontShield(Transform _TransInfo) : Object(_TransInfo) {}

FrontShield::~FrontShield() {}

Object* FrontShield::Initialize(string _Key)
{
    strKey = _Key;

    Buffer[0] = (char*)"¦£¦¡¦¤";
    Buffer[1] = (char*)"¦¢£½¦¢";
    Buffer[2] = (char*)"¦¦¦¡¦¥";

    TransInfo.Position = Vector3(float(0.0f), float(0.0f));
    TransInfo.Rotation = Vector3(0.0f, 0.0f);
    TransInfo.Scale = Vector3(5.0f, 3.0f);

    return this;
}

int FrontShield::Update()
{
    Object* pPlayer = ObjectManager::GetInstance()->GetObjectList("Player")->front();
    
    TransInfo.Position.x = pPlayer->GetPosition().x + 9.5f;
    TransInfo.Position.y = pPlayer->GetPosition().y + 0.25f;

    return 0;
}

void FrontShield::Render()
{
    for (int i = 0; i < 3; ++i)
    {
        CursorManager::GetInstance()->WriteBuffer(
            TransInfo.Position.x,
            TransInfo.Position.y - (TransInfo.Scale.y * 0.5f) + i,
            Buffer[i], 15);
    }
}

void FrontShield::Release()
{
}
