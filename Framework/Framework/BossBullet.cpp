#include "BossBullet.h"
#include "MathManager.h"
#include "CursorManager.h"

BossBullet::BossBullet()
{
}

BossBullet::~BossBullet()
{
}

void BossBullet::Initialize()
{
    BridgeKey = "BossBullet";

    Speed = -1.75f;
    Color = 15;
}

int BossBullet::Update(Transform& Info)
{
    Info.Direction = MathManager::GetDirection(
        Info.Position, Vector3(0.0f, Info.Position.y));

    Info.Position -= Info.Direction * Speed;

    return 0;
}

void BossBullet::Render()
{
    CursorManager::GetInstance()->WriteBuffer(
        pObject->GetPosition().x + (pObject->GetScale().x * 0.5f),
        pObject->GetPosition().y - (pObject->GetScale().y * 0.5f),
        (char*)"£ª",
        Color);

    CursorManager::GetInstance()->WriteBuffer(
        pObject->GetPosition().x + (pObject->GetScale().x * 0.5f),
        pObject->GetPosition().y + (pObject->GetScale().y * 0.25f),
        (char*)"£ª",
        Color);
}

void BossBullet::Release()
{
}
