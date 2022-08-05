#include "Boss.h"
//#include "CursorManager.h"
//#include "ObjectManager.h"
//#include "ScoreManager.h"
//#include "EnemyBullet.h"
//#include "BossBullet.h"
#include "Bridge.h"

Boss::Boss() {}

Boss::Boss(Transform _TransInfo) : Object(_TransInfo) {}

Boss::~Boss() {}

Object* Boss::Initialize(string _Key)
{
	strKey = _Key;

    //Buffer[0] = (char*)"����������";
    //Buffer[1] = (char*)"����������";
    //Buffer[2] = (char*)"����������";
    //Buffer[3] = (char*)"����������";
    //Buffer[4] = (char*)"���ߣߣߦ�";
    //Buffer[5] = (char*)"���ߣߣߡ�";

    TransInfo.Position = Vector3(0.0f, 0.0f);
    TransInfo.Rotation = Vector3(0.0f, 0.0f);
    TransInfo.Scale = Vector3(12.0f, 6.0f);

    TransInfo.Direction = Vector3(0.0f, 0.0f);

    if (pBridge)
        pBridge->Initialize();

	return this;
}

int Boss::Update()
{
    if (pBridge)
        pBridge->Update(TransInfo);

	return 0;
}

void Boss::Render()
{
    if (pBridge)
        pBridge->Render();
}

void Boss::Release()
{
    delete pBridge;
    pBridge = nullptr;
}
