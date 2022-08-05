#include "BossParts_LeftArms.h"
#include "ObjectManager.h"
#include "CursorManager.h"
#include "MathManager.h"

BossParts_LeftArms::BossParts_LeftArms() {}

BossParts_LeftArms::~BossParts_LeftArms() {}

void BossParts_LeftArms::Initialize()
{
    BridgeKey = "BossParts_LeftArms";

    BossPartsText[0] = (char*)"";
    BossPartsText[1] = (char*)"";
    BossPartsText[2] = (char*)"";
    BossPartsText[3] = (char*)"";
    BossPartsText[4] = (char*)"";
    BossPartsText[5] = (char*)"";
}

int BossParts_LeftArms::Update(Transform& Info)
{
    return 0;
}

void BossParts_LeftArms::Render()
{
}

void BossParts_LeftArms::Release()
{
}
