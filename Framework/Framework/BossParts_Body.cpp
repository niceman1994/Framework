#include "BossParts_Body.h"
#include "BossParts_LeftArms.h"
#include "BossParts_RightArms.h"
#include "ObjectManager.h"
#include "CursorManager.h"
#include "MathManager.h"
#include "Prototype.h"
#include "BossNormalBullet.h"

BossParts_Body::BossParts_Body() {}

BossParts_Body::~BossParts_Body() {}

void BossParts_Body::Initialize()
{
    BridgeKey = "BossParts_Body";

    //BossPartsText[9] = (char*)"忙式式式式式忖";
    //BossPartsText[6] = (char*)"弛   ﹥﹤﹤ 弛";
    //BossPartsText[7] = (char*)"弛﹥﹤﹥﹤  弛";
    //BossPartsText[8] = (char*)"弛  ﹥﹥﹤﹤弛";
    //BossPartsText[5] = (char*)"戌式式式式式戎";

    BossPartsText[0] = (char*)"ㄞ����������′";
    BossPartsText[1] = (char*)"弛����������弛";
    BossPartsText[2] = (char*)"弛  仃仃仃  弛";
    BossPartsText[3] = (char*)"弛�舝舝舝舝艀�";
    BossPartsText[4] = (char*)"′�舝舝舝舝舝�";
    
    //BossPartsText[10] = (char*)"忙式式式式式忖";
    //BossPartsText[11] = (char*)"弛  ﹥﹥﹤﹤弛";
    //BossPartsText[12] = (char*)"弛﹥﹤﹥﹤  弛";
    //BossPartsText[13] = (char*)"弛   ﹥﹤﹤ 弛";
    //BossPartsText[14] = (char*)"戌式式式式式戎";

    Bridge* Left_Bridge = new BossParts_LeftArms;
    ObjectManager::GetInstance()->AddObject("Boss", Left_Bridge, 200.0f, 20.0f);

    Bridge* Right_Bridge = new BossParts_RightArms;
    ObjectManager::GetInstance()->AddObject("Boss", Right_Bridge, 200.0f, 30.0f);

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

    if (Info.Position.x <= 178.0f && rand() % 20 == 10)
    {
        Bridge* pBridge = new BossNormalBullet;
        ObjectManager::GetInstance()->AddObject("EnemyBullet", pBridge, Info.Position);
    }
    if (Info.Position.x <= 178.0f && rand() % 20 == 10)
    {
        Bridge* pBridge = new BossNormalBullet;
        ObjectManager::GetInstance()->AddObject("EnemyBullet", pBridge, Info.Position.x, Info.Position.y - 1.0f);
    }
    if (Info.Position.x <= 178.0f && rand() % 20 == 10)
    {
        Bridge* pBridge = new BossNormalBullet;
        ObjectManager::GetInstance()->AddObject("EnemyBullet", pBridge, Info.Position.x, Info.Position.y + 1.0f);
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
}

void BossParts_Body::Release()
{
}
