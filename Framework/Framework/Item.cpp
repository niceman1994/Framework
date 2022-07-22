#include "Item.h"
#include "Bridge.h"
#include "CursorManager.h"
#include "ObjectManager.h"
//#include "ScoreItem.h"
//#include "ShieldItem.h"

Item::Item() {}

Item::Item(Transform _TransInfo) : Object(_TransInfo) {}

Item::~Item() { Release(); }

Object* Item::Initialize(string _Key)
{
    strKey = _Key;

    Buffer[0] = (char*)"¦£¦¡¦¤";
    Buffer[1] = (char*)"¦¢£¿¦¢";
    Buffer[2] = (char*)"¦¦¦¡¦¥";

    TransInfo.Position = Vector3(0.0f, 0.0f);
    TransInfo.Rotation = Vector3(0.0f, 0.0f);
    TransInfo.Scale = Vector3(7.0f, 3.0f);

    if (pBridge)
        pBridge->Initialize();

    return this;
}

int Item::Update()
{
    //TransInfo.Position.x -= 1.2f * 1;

    if (pBridge)
        pBridge->Update(TransInfo);

    //if (Key == "ShieldItem")
    //{
    //    Bridge* pBridge = new ShieldItem;
    //    ObjectManager::GetInstance()->AddObject("Item", pBridge, TransInfo.Position);
    //}
    //else if (Key == "ScoreItem")
    //{
    //    Bridge* pBridge = new ScoreItem;
    //    ObjectManager::GetInstance()->AddObject("Item", pBridge, TransInfo.Position);
    //}

    return 0;
}

void Item::Render()
{
    if (pBridge)
        pBridge->Render();
}

void Item::Release()
{
    delete pBridge;
    pBridge = nullptr;
}
