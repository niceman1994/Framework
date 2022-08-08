#include "BossNormalBullet.h"
#include "MathManager.h"
#include "CursorManager.h"

BossNormalBullet::BossNormalBullet()
{
}

BossNormalBullet::~BossNormalBullet()
{
}

void BossNormalBullet::Initialize()
{
    BridgeKey = "BossNormalBullet";

    Speed = -1.75f;
    Color = 15;
}

int BossNormalBullet::Update(Transform& Info)
{
    Info.Direction = MathManager::GetDirection(
        Info.Position, Vector3(0.0f, Info.Position.y));

    Info.Position -= Info.Direction * Speed;

    return 0;
}

void BossNormalBullet::Render()
{
    CursorManager::GetInstance()->WriteBuffer(
        pObject->GetPosition().x + (pObject->GetScale().x),
        pObject->GetPosition().y - (pObject->GetScale().y * 0.33f),
        (char*)"£ª",
        Color);
}

void BossNormalBullet::Release()
{
}
