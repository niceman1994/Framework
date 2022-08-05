#include "BossParts_RightArms.h"
#include "ObjectManager.h"
#include "CursorManager.h"
#include "MathManager.h"

BossParts_RightArms::BossParts_RightArms() {}

BossParts_RightArms::~BossParts_RightArms() {}

void BossParts_RightArms::Initialize()
{
    BridgeKey = "BossParts_RightArms";

    //BossPartsText[0] = (char*)"忙式式式式式式式忖";
    //BossPartsText[1] = (char*)"弛    ﹥﹥﹤﹤  弛";
    //BossPartsText[2] = (char*)"弛  ﹥﹤﹥﹤    弛";
    //BossPartsText[3] = (char*)"弛     ﹥﹤﹤﹤ 弛";
    //BossPartsText[4] = (char*)"戌式式式式式式式戎";

    Speed = -1.0f;
    Color = 15;
}

int BossParts_RightArms::Update(Transform& Info)
{
    Info.Direction = MathManager::GetDirection(
        Info.Position, Vector3(0.0f, Info.Position.y));

    Info.Position -= Info.Direction * Speed;

    return 0;
}

void BossParts_RightArms::Render()
{
    //for (int i = 0; i < 5; ++i)
    //{
    //    CursorManager::GetInstance()->WriteBuffer(
    //        pObject->GetPosition().x - (pObject->GetScale().x * 3.0f),
    //        pObject->GetPosition().y - (pObject->GetScale().y * 4.0f) + i,
    //        BossPartsText[i], Color);
    //}
}

void BossParts_RightArms::Release()
{
}
