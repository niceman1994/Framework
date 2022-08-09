#include "BossParts_RightArms.h"
#include "ObjectManager.h"
#include "CursorManager.h"
#include "MathManager.h"
#include "BossSpecialBullet.h"

BossParts_RightArms::BossParts_RightArms() {}

BossParts_RightArms::~BossParts_RightArms() {}

void BossParts_RightArms::Initialize()
{
    BridgeKey = "BossParts_RightArms";

    BossPartsText[0] = (char*)"��������������";
    BossPartsText[1] = (char*)"��  ����ঢ";
    BossPartsText[2] = (char*)"�������  ��";
    BossPartsText[3] = (char*)"��   ���� ��";
    BossPartsText[4] = (char*)"��������������";

    Speed = -1.0f;
    Color = 15;
}

int BossParts_RightArms::Update(Transform& Info)
{
    Info.Direction = MathManager::GetDirection(
        Info.Position, Vector3(150.0f, Info.Position.y));

    if (Info.Position.x > 150.0f)
        Info.Position -= Info.Direction * Speed;

    if (Info.Position.x <= 178.0f && rand() % 50 == 10)
    {
        Bridge* pBridge = new BossSpecialBullet;
        ObjectManager::GetInstance()->AddObject("EnemyBullet", pBridge, Info.Position);
    }
    if (Info.Position.x <= 178.0f && rand() % 50 == 10)
    {
        Bridge* pBridge = new BossSpecialBullet;
        ObjectManager::GetInstance()->AddObject("EnemyBullet", pBridge, Info.Position.x - 1.0f, Info.Position.y - 1.0f);
    }
    if (Info.Position.x <= 178.0f && rand() % 50 == 10)
    {
        Bridge* pBridge = new BossSpecialBullet;
        ObjectManager::GetInstance()->AddObject("EnemyBullet", pBridge, Info.Position.x - 1.0f, Info.Position.y + 1.0f);
    }

    return 0;
}

void BossParts_RightArms::Render()
{
    for (int i = 0; i < 5; ++i)
    {
        CursorManager::GetInstance()->WriteBuffer(
            pObject->GetPosition().x,
            pObject->GetPosition().y - (pObject->GetScale().y * 0.5f) + i,
            BossPartsText[i], Color);
    }
}

void BossParts_RightArms::Release()
{
}
