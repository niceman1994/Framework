#include "Enemy2.h"
#include "CursorManager.h"
#include "ObjectManager.h"

Enemy2::Enemy2() {}

Enemy2::Enemy2(Transform _TransInfo) : Object(_TransInfo) {}

Enemy2::~Enemy2() {}

Object* Enemy2::Initialize(string _Key)
{
    strKey = _Key;

    Buffer[0] = (char*)" ж╟";
    Buffer[1] = (char*)"  бл     бл";
    Buffer[2] = (char*)"г▀бл     блг▀";

    TransInfo.Position = Vector3(0.0f, 0.0f);
    TransInfo.Rotation = Vector3(0.0f, 0.0f);
    TransInfo.Scale = Vector3(14.0f, 5.0f);

    return this;
}

int Enemy2::Update()
{
    int time = rand() % 100 + 1;

    if (time == 5 || time == 6 || time == 7)
        TransInfo.Position.x += 2.0f;
    else if (time == 10 || time == 11 || time == 12)
         TransInfo.Position.x -= 2.0f;

    return 0;
}

void Enemy2::Render()
{
    for (int i = 0; i < 3; ++i)
    {
        CursorManager::GetInstance()->WriteBuffer(
            TransInfo.Position.x,
            TransInfo.Position.y - (TransInfo.Scale.y * 0.5f) + i,
            Buffer[i], 15);
    }
}

void Enemy2::Release()
{
}
