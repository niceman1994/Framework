#include "NormalEnemyBullet.h"
#include "MathManager.h"
#include "CursorManager.h"
#include "ObjectManager.h"

NormalEnemyBullet::NormalEnemyBullet() {}

NormalEnemyBullet::~NormalEnemyBullet() {}

void NormalEnemyBullet::Initialize()
{
    Speed = -1.75f;
    Color = 15;
}

int NormalEnemyBullet::Update(Transform& Info)
{
    Object* pPlayer = ObjectManager::GetInstance()->GetObjectList("Player")->front();

    float Distance = MathManager::GetDistance(
        Info.Position, Vector3(pPlayer->GetPosition()));

    Vector3 TargetDistance;
    TargetDistance.x = pPlayer->GetPosition().x / Distance - pPlayer->GetPosition().y;
    TargetDistance.y = pPlayer->GetPosition().y;

    Info.Direction = MathManager::GetDirection(
        Info.Position, Vector3(TargetDistance));

    Info.Position -= Info.Direction * Speed;

    return 0;
}

void NormalEnemyBullet::Render()
{
    CursorManager::GetInstance()->WriteBuffer(
        pObject->GetPosition().x + (pObject->GetScale().x),
        pObject->GetPosition().y - pObject->GetScale().y * 0.33f,
        (char*)"£ª", Color);
}

void NormalEnemyBullet::Release()
{
}
