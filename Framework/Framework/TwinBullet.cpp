#include "TwinBullet.h"
#include "CursorManager.h"
#include "MathManager.h"
#include "Object.h"

TwinBullet::TwinBullet()
{
}

TwinBullet::~TwinBullet()
{
}

void TwinBullet::Initialize()
{
    Speed = 0.65f;
    Color = 13;
}

int TwinBullet::Update(Transform& Info)
{
    Info.Direction = MathManager::GetDirection(
        Info.Position, Vector3(120.0f, Info.Position.y));

    //Info.Direction = MathManager::GetDirection(
    //    Info.Position, Vector3(Info.Position.x, Info.Position.y));

    Info.Position += Info.Direction * Speed;

    return 0;
}

void TwinBullet::Render()
{
    CursorManager::GetInstance()->WriteBuffer(
        pObject->GetPosition().x + (pObject->GetScale().x),
        pObject->GetPosition().y - (pObject->GetScale().y * 0.5f),
        (char*)"£ª",
        Color);

    CursorManager::GetInstance()->WriteBuffer(
        pObject->GetPosition().x + (pObject->GetScale().x),
        pObject->GetPosition().y + (pObject->GetScale().y * 0.25f),
        (char*)"£ª",
        14);
}

void TwinBullet::Release()
{
}
