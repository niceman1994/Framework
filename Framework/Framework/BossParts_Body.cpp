#include "BossParts_Body.h"
#include "ObjectManager.h"
#include "CursorManager.h"
#include "MathManager.h"
#include "BossBullet.h"

BossParts_Body::BossParts_Body() {}

BossParts_Body::~BossParts_Body() {}

void BossParts_Body::Initialize()
{
    BridgeKey = "BossParts_Body";

    BossPartsText[0] = (char*)"¡¬£þ£þ£þ£¯ ";
    BossPartsText[1] = (char*)"¦¢£þ£þ£þ¦¢ ";
    BossPartsText[2] = (char*)"¦¢¤±¤±¤±¦¢ ";
    BossPartsText[3] = (char*)"¦¢¤±¤±¤±¦¢ ";
    BossPartsText[4] = (char*)"¦¢£ß£ß£ß¦¢ ";
    BossPartsText[5] = (char*)"£¯£ß£ß£ß¡¬ ";

    Speed = -1.0f;
    Color = 15;
}

int BossParts_Body::Update(Transform& Info)
{
    Object* pBoss = ObjectManager::GetInstance()->GetObjectList("Boss")->front();

    Info.Direction = MathManager::GetDirection(
        Info.Position, Vector3(150.0f, Info.Position.y));

    Info.Position -= Info.Direction * Speed;

    pBoss->SetPosition(Info.Position);

    if (Info.Position.x <= 178.0f && rand() % 20 == 1)
    {
        Bridge* pBridge = new BossBullet;
        ObjectManager::GetInstance()->AddObject("EnemyBullet", pBridge, Info.Position);
    }

    return 0;
}

void BossParts_Body::Render()
{
    for (int i = 0; i < 6; ++i)
    {
        CursorManager::GetInstance()->WriteBuffer(
            pObject->GetPosition().x,
            pObject->GetPosition().y - (pObject->GetScale().y * 0.5f) + i,
            BossPartsText[i], Color);
    }
}

void BossParts_Body::Release()
{
}
