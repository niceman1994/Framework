#include "TwinBullet.h"
#include "CursorManager.h"
#include "MathManager.h"

TwinBullet::TwinBullet() {}

TwinBullet::~TwinBullet() {}

void TwinBullet::Initialize()
{
    BridgeKey = "TwinBullet";

    Speed = 1.35f;
    Color = 13;
}

int TwinBullet::Update(Transform& Info)
{
    Info.Direction = MathManager::GetDirection(
        Info.Position, Vector3(180.0f, Info.Position.y));

    Info.Position += Info.Direction * Speed;

    return 0;
}

void TwinBullet::Render()
{
    CursorManager::GetInstance()->WriteBuffer(
        pObject->GetPosition().x + (pObject->GetScale().x * 0.5f),
        pObject->GetPosition().y - (pObject->GetScale().y * 0.5f),
        (char*)"��",
        Color);
    
    CursorManager::GetInstance()->WriteBuffer(
        pObject->GetPosition().x + (pObject->GetScale().x * 0.5f),
        pObject->GetPosition().y + (pObject->GetScale().y * 0.25f),
        (char*)"��",
        14);
}

void TwinBullet::Release()
{
}
