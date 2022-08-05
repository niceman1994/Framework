#include "BossParts_Body.h"
#include "BossParts_LeftArms.h"
#include "BossParts_RightArms.h"
#include "ObjectManager.h"
#include "CursorManager.h"
#include "MathManager.h"
#include "BossNormalBullet.h"

BossParts_Body::BossParts_Body() {}

BossParts_Body::~BossParts_Body() {}

void BossParts_Body::Initialize()
{
    BridgeKey = "BossParts_Body";

    BossPartsText[0] = (char*)"¡¬£þ£þ£þ£¯ ";
    BossPartsText[1] = (char*)"¦¢£þ£þ£þ¦¢ ";
    BossPartsText[2] = (char*)"¦¢¤±¤±¤±¦¢ ";
    BossPartsText[3] = (char*)"¦¢£ß£ß£ß¦¢ ";
    BossPartsText[4] = (char*)"£¯£ß£ß£ß¡¬ ";

    BossPartsText[5] = (char*)"¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤";
    BossPartsText[6] = (char*)"¦¢     ¡á¡à¡à¡à ¦¢";
    BossPartsText[7] = (char*)"¦¢  ¡á¡à¡á¡à    ¦¢";
    BossPartsText[8] = (char*)"¦¢    ¡á¡á¡à¡à  ¦¢";
    BossPartsText[9] = (char*)"¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥";

    BossPartsText[10] = (char*)"¦£¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¤";
    BossPartsText[11] = (char*)"¦¢    ¡á¡á¡à¡à  ¦¢";
    BossPartsText[12] = (char*)"¦¢  ¡á¡à¡á¡à    ¦¢";
    BossPartsText[13] = (char*)"¦¢     ¡á¡à¡à¡à ¦¢";
    BossPartsText[14] = (char*)"¦¦¦¡¦¡¦¡¦¡¦¡¦¡¦¡¦¥";

    Speed = -1.0f;
    Color = 15;
}

int BossParts_Body::Update(Transform& Info)
{
    Info.Direction = MathManager::GetDirection(
        Info.Position, Vector3(150.0f, Info.Position.y));

    if (Info.Position.x > 150.0f)
        Info.Position -= Info.Direction * Speed;

    //if (rand() % 10 == 0 && Info.Position.y > 15.0f)
    //    Info.Position.y -= 2.0f;
    //else if (rand() % 10 == 1 && Info.Position.y < 35.0f)
    //    Info.Position.y += 2.0f;

    if (Info.Position.x <= 178.0f && rand() % 20 == 1)
    {
        Bridge* pBridge = new BossNormalBullet;
        ObjectManager::GetInstance()->AddObject("EnemyBullet", pBridge, Info.Position);
    }

    if (Info.Position.x <= 178.0f && ObjectManager::GetInstance()->GetHitCount() >= 50)
    {
        if (rand() % 50 == 1)
        {
            Bridge* pBridge = new BossParts_LeftArms;
            ObjectManager::GetInstance()->AddObject("EnemyBullet", pBridge, Info.Position);
        }
    }

    if (Info.Position.x <= 178.0f && ObjectManager::GetInstance()->GetHitCount() >= 50)
    {
        if (rand() % 50 == 2)
        {
            Bridge* pBridge = new BossParts_RightArms;
            ObjectManager::GetInstance()->AddObject("EnemyBullet", pBridge, Info.Position);
        }
    }

    return 0;
}

void BossParts_Body::Render()
{
    //CursorManager::GetInstance()->WriteBuffer(0.0f, 45.0f, pObject->GetPosition().x);
    //CursorManager::GetInstance()->WriteBuffer(0.0f, 46.0f, pObject->GetPosition().y);

    for (int i = 0; i < 5; ++i)
    {
        CursorManager::GetInstance()->WriteBuffer(
            pObject->GetPosition().x,
            pObject->GetPosition().y - (pObject->GetScale().y * 0.5f) + i,
            BossPartsText[i], Color);
    }

    if (ObjectManager::GetInstance()->GetHitCount() >= 50)
    {
        //for (int i = 5; i < 10; ++i)
        //{
        //    CursorManager::GetInstance()->WriteBuffer(
        //        pObject->GetPosition().x - (pObject->GetScale().x * 0.75f),
        //        pObject->GetPosition().y - (pObject->GetScale().y * 0.35f) + i,
        //        BossPartsText[i], Color);
        //}
        //
        //for (int i = 10; i < 15; ++i)
        //{
        //    CursorManager::GetInstance()->WriteBuffer(
        //        pObject->GetPosition().x - (pObject->GetScale().x * 0.75f),
        //        pObject->GetPosition().y - (pObject->GetScale().y * 3.0f) + i,
        //        BossPartsText[i], Color);
        //}

        for (int i = 5; i < 10; ++i)
        {
            CursorManager::GetInstance()->WriteBuffer(
                pObject->GetPosition().x - 6.0f,
                pObject->GetPosition().y - 10.0f - (pObject->GetScale().y * 0.5f) + i,
                BossPartsText[i], Color);
        }

        for (int i = 10; i < 15; ++i)
        {
            CursorManager::GetInstance()->WriteBuffer(
                pObject->GetPosition().x - 6.0f,
                pObject->GetPosition().y - 5.0f - (pObject->GetScale().y * 0.5f) + i,
                BossPartsText[i], Color);
        }
    }
}

void BossParts_Body::Release()
{
}
