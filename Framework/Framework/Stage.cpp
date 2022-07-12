#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "ScrollBox.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "InputManager.h"
#include "CursorManager.h"
#include "ObjectManager.h"
#include "Prototype.h"
#include "ObjectFactory.h"
#include "ObjectPool.h"
#include "StageUI.h"

Stage::Stage() : pPlayer(nullptr), pUI(nullptr), Check(0) { }
Stage::~Stage() { Release(); }


void Stage::Initialize()
{
	Check = 0;

	pUI = new ScrollBox;
	pUI->Initialize();

	ObjectManager::GetInstance()->AddObject("Player");
	pPlayer = ObjectManager::GetInstance()->GetObjectList("Player")->front();

	Object* pEnemy = Prototype::GetInstance()->ProtoTypeObject("Enemy");

	for (int i = 0; i < 5; ++i)
	{
		srand(DWORD(GetTickCount64() * (i + 1)));
		
		pEnemy->SetPosition(float(rand() % 30 + 80), float(rand() % 18 + 5));
		ObjectManager::GetInstance()->AddObject("Enemy");
	}
}

void Stage::Update()
{
	list<Object*>* pBulletList = ObjectManager::GetInstance()->GetObjectList("Bullet");
	list<Object*>* pEnemyList = ObjectManager::GetInstance()->GetObjectList("Enemy");

	DWORD dwKey = InputManager::GetInstance()->GetKey();

	if (dwKey & KEY_TAB)
	{
		Enable_UI();
	}

	if (dwKey & PRESS_5)
	{
		ObjectManager::GetInstance()->IncreaseCredit();
		CursorManager::GetInstance()->ClearBuffer();
		Sleep(100);

		if (ObjectManager::GetInstance()->GetCredit() >= 99)
			ObjectManager::GetInstance()->SetCredit(99);
	}

	pPlayer->Update();
	ObjectManager::GetInstance()->Update();
	
	if (dwKey & KEY_ESCAPE)
	{
		if (pBulletList->size() >= 20)
		{
			for (int i = 0; i < 20; ++i)
			{
				ObjectPool::GetInstance()->CatchObject(pBulletList->back());
				pBulletList->pop_back();
			}
		}
		else if (pBulletList->size() < 20 && pBulletList->size() >= 10)
		{
			for (int i = 0; i < 10; ++i)
			{
				ObjectPool::GetInstance()->CatchObject(pBulletList->back());
				pBulletList->pop_back();
			}
		}
		else if (pBulletList->size() < 10 && pBulletList->size() >= 5)
		{
			for (int i = 0; i < 5; ++i)
			{
				ObjectPool::GetInstance()->CatchObject(pBulletList->back());
				pBulletList->pop_back();
			}
		}
		else if (pBulletList->size())
		{
			ObjectPool::GetInstance()->CatchObject(pBulletList->back());
			pBulletList->pop_back();
		}
	}

	if (pBulletList != nullptr)
	{
		for (list<Object*>::iterator iter = pBulletList->begin();
			iter != pBulletList->end(); )
		{
			if ((*iter)->GetPosition().x >= 120.0f)
				iter = ObjectManager::GetInstance()->ThrowObject(iter, (*iter));
			else
				++iter;
		}
	}

	if (pEnemyList != nullptr)
	{
		for (list<Object*>::iterator iter = pEnemyList->begin(); iter != pEnemyList->end();)
		{
			if ((*iter)->GetPosition().x <= 0.0f)
				iter = ObjectManager::GetInstance()->ThrowObject(iter, *iter);
			else
				++iter;
		}
	}

	if (pPlayer != nullptr)
	{
		if (pEnemyList != nullptr && pBulletList != nullptr)
		{
			for (list<Object*>::iterator Bulletiter = pBulletList->begin(); Bulletiter != pBulletList->end();)
			{
				for (list<Object*>::iterator Enemyiter = pEnemyList->begin(); Enemyiter != pEnemyList->end();)
				{
					if (CollisionManager::Collision(*Bulletiter, *Enemyiter))
					{
						delete (*Bulletiter);
						Bulletiter = pBulletList->erase(Bulletiter);

						delete (*Enemyiter);
						Enemyiter = pEnemyList->erase(Enemyiter);
					}

					if (Enemyiter != pEnemyList->end())
						++Enemyiter;
				}
				++Bulletiter;
			}

			//if (CollisionManager::CircleCollision(pPlayer, *Enemyiter))
			//{
			//	Enemyiter = ObjectManager::GetInstance()->ThrowObject(Enemyiter, (*Enemyiter));
			//}
			//else
			//	++Enemyiter;
		}
	}

	if (Check)
		pUI->Update();
}

void Stage::Render()
{
	pPlayer->Render();

	ObjectManager::GetInstance()->Render();

	if (Check)
		pUI->Render();

	CursorManager::GetInstance()->WriteBuffer(119.0f, 28.0f, (char*)"\t\t\t\t\t\t\t\t\t\t\t\tCREDIT : ", 14);
	CursorManager::GetInstance()->WriteBuffer(97.0f, 29.0f, (int)(char*)(ObjectManager::GetInstance()->GetCredit()), 14);
}

void Stage::Release()
{
	delete pPlayer;
	pPlayer = nullptr;
}

void Stage::Enable_UI()
{
	Check = !Check;
}
