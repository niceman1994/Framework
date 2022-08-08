#include "BossSpecialBullet.h"
#include "MathManager.h"
#include "CursorManager.h"
#include "ObjectManager.h"

BossSpecialBullet::BossSpecialBullet() {}

BossSpecialBullet::~BossSpecialBullet() {}

void BossSpecialBullet::Initialize()
{
    BridgeKey = "BossSpecialBullet";

    Speed = -1.5f;
    Color = 12;
}

int BossSpecialBullet::Update(Transform& Info)
{
    Object* pPlayer = ObjectManager::GetInstance()->GetObjectList("Player")->front();

    Info.Direction = MathManager::GetDirection(
        Info.Position, Vector3(pPlayer->GetPosition()));

    Info.Position -= Info.Direction * Speed;

    return 0;
}

void BossSpecialBullet::Render()
{
    CursorManager::GetInstance()->WriteBuffer(
        pObject->GetPosition().x + (pObject->GetScale().x),
        pObject->GetPosition().y - pObject->GetScale().y * 0.33f,
        (char*)"¡¶", Color);
}

void BossSpecialBullet::Release()
{
}
