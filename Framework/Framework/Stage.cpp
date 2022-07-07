#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "ScrollBox.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "InputManager.h"
#include "CursorManager.h"
#include "ObjectManager.h"
#include "ObjectFactory.h"
#include "ObjectPool.h"

Stage::Stage() : Check(0) { }
Stage::Stage(int _Score) : Scene(_Score) {}
Stage::~Stage() { Release(); }


void Stage::Initialize()
{
	Check = 0;
	Score = 0;

	Object* pEnemyProto = ObjectFactory<Enemy>::CreateObject();

	pUI = new ScrollBox;
	pUI->Initialize();

	for (int i = 0; i < 7; ++i)
	{
		srand(DWORD(GetTickCount64() * (i + 1)));

		Object* pEnemy = pEnemyProto->Clone();
		//pEnemy->SetPosition(118.0f, float(rand() % 30));
		pEnemy->SetPosition(float(rand() % 15 + 80), float(rand() % 27 + 3));

		ObjectManager::GetInstance()->AddObject(pEnemy);
	}
}

void Stage::Update()
{
	DWORD dwKey = InputManager::GetInstance()->GetKey();

	if (dwKey & KEY_TAB)
	{
		Enable_UI();
	}

	ObjectManager::GetInstance()->Update();

	Object* pPlayer = ObjectManager::GetInstance()->GetObjectList("Player")->front();
	list<Object*>* pBulletList = ObjectManager::GetInstance()->GetObjectList("Bullet");
	list<Object*>* pEnemyList = ObjectManager::GetInstance()->GetObjectList("Enemy");

	if (pBulletList != nullptr)
	{
		for (list<Object*>::iterator iter = pBulletList->begin();
			iter != pBulletList->end(); )
		{
			if ((*iter)->GetPosition().x >= 119.5f)
				iter = pBulletList->erase(iter);
			//else if ((*iter)->GetPosition().x >= 59.5f && (*iter)->GetPosition().x <= 60.5f)
			//	iter = pBulletList->erase(iter);
			else
				++iter;
		}
	}

	if (pPlayer != nullptr)
	{
		if (pEnemyList != nullptr)
		{
			for (list<Object*>::iterator Enemyiter = pEnemyList->begin();
				Enemyiter != pEnemyList->end(); ++Enemyiter)
			{
				if (CollisionManager::CircleCollision(pPlayer, *Enemyiter))
				{
					
				}

				if (pBulletList != nullptr)
				{
					for (list<Object*>::iterator Bulletiter = pBulletList->begin(); Bulletiter != pBulletList->end(); ++Bulletiter)
					{
						if (CollisionManager::CircleCollision(*Bulletiter, *Enemyiter))
						{

						}
					}
				}
			}
		}

		/*if (pBulletList != nullptr && pEnemyList != nullptr)
		{
			for (list<Object*>::iterator Bulletiter = pBulletList->begin();
				Bulletiter != pBulletList->end(); ++Bulletiter)
			{
				for (list<Object*>::iterator Enemyiter = pEnemyList->begin(); Enemyiter != pEnemyList->end();)
				{
					if (CollisionManager::Collision(*Bulletiter, *Enemyiter))
					{
						Object* EnemyTemp = *Enemyiter;
						Enemyiter = pEnemyList->erase(Enemyiter);

						delete EnemyTemp;
						EnemyTemp = nullptr;
					}
					else
						++Enemyiter;
				}
			}
		}*/
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
