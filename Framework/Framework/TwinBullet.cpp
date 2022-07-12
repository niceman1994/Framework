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
    //Info.Direction = MathManager::GetDirection(
    //    Info.Position, Vector3(60.0f, 15.0f));

    Info.Direction = MathManager::GetDirection(
        Info.Position, Vector3(Info.Position.x, Info.Position.y));

    Info.Position += Info.Direction * Speed;

    return 0;
}

void TwinBullet::Render()
{
    CursorManager::GetInstance()->WriteBuffer(
        pObject->GetPosition().x - (pObject->GetPosition().y * 0.5f),
        pObject->GetPosition().y - 1,
        (char*)"¦¡",
        Color);

    CursorManager::GetInstance()->WriteBuffer(
        pObject->GetPosition().x - (pObject->GetPosition().y * 0.5f),
        pObject->GetPosition().y,
        (char*)"¦¡",
        Color);
}

void TwinBullet::Release()
{
}
