#include "Item.h"
#include "ObjectManager.h"
#include "CursorManager.h"

Item::Item() {}

Item::Item(Transform _TransInfo) : Object(_TransInfo) {}

Item::~Item() {}

Object* Item::Initialize(string _Key)
{
    strKey = _Key;

    Buffer[0] = (char*)"¦£¦¡¦¤";
    Buffer[1] = (char*)"¦¢£¿¦¢";
    Buffer[2] = (char*)"¦¦¦¡¦¥";

    TransInfo.Position = Vector3(0.0f, 0.0f);
    TransInfo.Rotation = Vector3(0.0f, 0.0f);
    TransInfo.Scale = Vector3(7.0f, 3.0f);

    return this;
}

int Item::Update()
{
    TransInfo.Position.x -= 0.8f;

    return 0;
}

void Item::Render()
{
    for (int i = 0; i < 3; ++i)
    {
        CursorManager::GetInstance()->WriteBuffer(
            TransInfo.Position.x,
            TransInfo.Position.y - (TransInfo.Scale.y * 0.5f) + i,
            Buffer[i], 15);
    }
}

void Item::Release()
{
}
