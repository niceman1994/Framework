#include "BossParts_LeftArms.h"
#include "ObjectManager.h"
#include "CursorManager.h"
#include "MathManager.h"

BossParts_LeftArms::BossParts_LeftArms() {}

BossParts_LeftArms::~BossParts_LeftArms() {}

void BossParts_LeftArms::Initialize()
{
    BridgeKey = "BossParts_LeftArms";

    //BossPartsText[0] = (char*)"忙式式式式式式式忖";
    //BossPartsText[1] = (char*)"弛     ﹥﹤﹤﹤ 弛";
    //BossPartsText[2] = (char*)"弛  ﹥﹤﹥﹤    弛";
    //BossPartsText[3] = (char*)"弛    ﹥﹥﹤﹤  弛";
    //BossPartsText[4] = (char*)"戌式式式式式式式戎";

    Speed = -1.f;
    Color = 15;
}

int BossParts_LeftArms::Update(Transform& Info)
{
    Info.Direction = MathManager::GetDirection(
        Info.Position, Vector3(0.0f, Info.Position.y));

    Info.Position -= Info.Direction * Speed;

    return 0;
}

void BossParts_LeftArms::Render()
{
   //for (int i = 0; i < 5; ++i)
   //{
   //    CursorManager::GetInstance()->WriteBuffer(
   //        pObject->GetPosition().x - (pObject->GetScale().x * 3.0f),
   //        pObject->GetPosition().y + (pObject->GetScale().y * 1.0f) + i,
   //        BossPartsText[i], Color);
   //}
}

void BossParts_LeftArms::Release()
{
}
