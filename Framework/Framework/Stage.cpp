#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "ScrollBox.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "CollisionManager.h"
#include "CursorManager.h"
#include "ObjectManager.h"
#include "ObjectFactory.h"

Stage::Stage() : Check(0) {}

Stage::~Stage() { Release(); }

void Stage::Initialize()
{
	Check = 0;

	Object* pEnemyProto = ObjectFactory<Enemy>::CreateObject();

	pUI = new ScrollBox;
	pUI->Initialize();

	for (int i = 0; i < 5; ++i)
	{
		srand(DWORD(GetTickCount64() * (i + 1))); // 8바이트에 4바이트를 캐스트해서 뜨는 경고

		Object* pEnemy = pEnemyProto->Clone();
		//pEnemy->SetPosition(118.0f, float(rand() % 30));
		pEnemy->SetPosition(float(rand() % 118), float(rand() % 30));

		ObjectManager::GetInstance()->AddObject(pEnemy);
	}
}

void Stage::Update()
{	// l 벨류, r 벨류
	DWORD dwKey = InputManager::GetInstance()->GetKey();

	if (dwKey & KEY_TAB)
		Enable_UI();

	ObjectManager::GetInstance()->Update();

	Object* pPlayer = ObjectManager::GetInstance()->GetObjectList("Player")->front();
	list<Object*>* pBulletList = ObjectManager::GetInstance()->GetObjectList("Bullet");
	list<Object*>* pEnemyList = ObjectManager::GetInstance()->GetObjectList("Enemy");

	if (pBulletList != nullptr)
	{
		for (list<Object*>::iterator iter = pBulletList->begin();
			iter != pBulletList->end();)
		{
			if ((*iter)->GetPosition().x >= 120.0f)
				iter = pBulletList->erase(iter); // 120.0f 의 위치에 있는걸 지우고 뒤쪽에 있는걸 붙여준 상태
			else if ((*iter)->GetPosition().x >= 59.5f && (*iter)->GetPosition().y >= 14.5f)
				iter = pBulletList->erase(iter);
			else
				++iter; // 미리 iter를 증가시키면 120.0f를 넘는지 확인할 방법이 없다.
		}
	}

	if (pPlayer != nullptr)
	{
		if (pEnemyList != nullptr)
		{
			for (list<Object*>::iterator Enemyiter = pEnemyList->begin(); Enemyiter != pEnemyList->end(); ++Enemyiter) // Enemyiter로 pEnemyList에 접근
			{
				if (CollisionManager::Collision(pPlayer, *Enemyiter)) // pPlayer와 Enemyiter의 충돌여부 검사
				{
					//CursorManager::Draw(50.0f, 1.0f, "충돌입니다.");
				}

				if (pBulletList != nullptr)
				{
					for (list<Object*>::iterator Bulletiter = pBulletList->begin(); Bulletiter != pBulletList->end(); ++Bulletiter) // Bulletiter로 pBulletList에 접근
					{
						if (CollisionManager::Collision(*Bulletiter, *Enemyiter)) // pPlayer와 *Enemyiter의 충돌여부 검사
						{
							//CursorManager::Draw(50.0f, 1.0f, "충돌입니다.");
						}
					}
				}
			}
		}
	}

	if (Check)
		pUI->Update();
}

void Stage::Render()
{
	ObjectManager::GetInstance()->Render();

	if (Check)
		pUI->Render();
}

void Stage::Release()
{
	
}

void Stage::Enable_UI()
{
	Check = !Check;
}
