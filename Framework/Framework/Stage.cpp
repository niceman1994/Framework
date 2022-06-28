#include "Stage.h"
#include "Enemy.h"
#include "SceneManager.h"
#include "CursorManager.h"
#include "ObjectManager.h"

Stage::Stage() : pPlayer(nullptr) {}

Stage::~Stage() { Release(); }

void Stage::Initialize()
{
	// 1. 반환형태가 Object* 이거나 && list<Object*>
	// 2. Key 가 전달되어야 함.
	//list<Object*>* pPlayerList = ObjectManager::GetInstance()->GetObjectList("Player");
	//
	//if(pPlayerList != nullptr)
	//	pPlayer = pPlayerList->front();
	Object* pEnemyProto = new Enemy;
	pEnemyProto->Initialize();

	for (int i = 0; i < 5; ++i)
	{
		srand(DWORD(GetTickCount64() * (i + 1))); // 8바이트에 4바이트를 캐스트해서 뜨는 경고

		Object* pEnemy = pEnemyProto->Clone();
		pEnemy->SetPosition(118.0f, float(rand() % 30));

		ObjectManager::GetInstance()->AddObject(pEnemy);
	}
}

void Stage::Update()
{	// l 벨류, r 벨류
	ObjectManager::GetInstance()->Update();

	list<Object*>* pBulletList = ObjectManager::GetInstance()->GetObjectList("＊");

	if (pBulletList != nullptr)
	{
		for (list<Object*>::iterator iter = pBulletList->begin(); iter != pBulletList->end();)
		{
			if ((*iter)->GetPosition().x >= 120.0f)
				iter = pBulletList->erase(iter); // 120.0f 의 위치에 있는걸 지우고 뒤쪽에 있는걸 붙여준 상태
			else
				++iter; // 미리 iter를 증가시키면 120.0f를 넘는지 확인할 방법이 없다.
		}
	}
}

void Stage::Render()
{
	ObjectManager::GetInstance()->Render();
}

void Stage::Release()
{
	::Safe_Delete(pPlayer);
}