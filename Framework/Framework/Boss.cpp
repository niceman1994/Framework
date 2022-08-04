#include "Boss.h"
#include "CursorManager.h"
#include "ObjectManager.h"
#include "ScoreManager.h"
#include "EnemyBullet.h"
#include "BossBullet.h"

Boss::Boss() {}

Boss::Boss(Transform _TransInfo) : Object(_TransInfo) {}

Boss::~Boss() {}

Object* Boss::Initialize(string _Key)
{
	strKey = _Key;

    Buffer[0] = (char*)"¡¬£þ£þ£þ£¯";
    Buffer[1] = (char*)"¦¢£þ£þ£þ¦¢";
    Buffer[2] = (char*)"¦¢¤±¤±¤±¦¢";
    Buffer[3] = (char*)"¦¢¤±¤±¤±¦¢";
    Buffer[4] = (char*)"¦¢£ß£ß£ß¦¢";
    Buffer[5] = (char*)"£¯£ß£ß£ß¡¬";

    TransInfo.Position = Vector3(870.0f, 25.0f);
    TransInfo.Rotation = Vector3(0.0f, 0.0f);
    TransInfo.Scale = Vector3(11.0f, 6.0f);

	return this;
}

int Boss::Update()
{
    TransInfo.Position.x -= 2.0f;
    
    if (TransInfo.Position.x <= 150.0f)
    {
        TransInfo.Position.x = 150.0f;

        if (rand() % 20 == 1)
        {
            Bridge* pBridge = new BossBullet;
            ObjectManager::GetInstance()->AddObject("EnemyBullet", pBridge, TransInfo.Position);
        }

        if (rand() % 10 == 0 || rand() % 10 == 1 || rand() % 10 == 2)
        {
            TransInfo.Position.y -= 1.0f;

            if (TransInfo.Position.y <= 15.0f)
                TransInfo.Position.y = 15.0f;
        }
        else if (rand() % 10 == 5 || rand() % 10 == 6 || rand() % 10 == 7 || rand() % 10 == 8)
        {
            TransInfo.Position.y += 1.0f;

            if (TransInfo.Position.y >= 35.0f)
                TransInfo.Position.y += 35.0f;
        }
    }

	return 0;
}

void Boss::Render()
{
    for (int i = 0; i < 6; ++i)
    {
        CursorManager::GetInstance()->WriteBuffer(
            TransInfo.Position.x,
            TransInfo.Position.y - (TransInfo.Scale.y * 0.5f) + i,
            Buffer[i]);
    }
}

void Boss::Release()
{
}
