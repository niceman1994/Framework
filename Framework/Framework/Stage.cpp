#include "Stage.h"
#include "Player.h"
#include "Enemy.h"
#include "ScrollBox.h"
#include "BackGround.h"
#include "SceneManager.h"
#include "CollisionManager.h"
#include "InputManager.h"
#include "CursorManager.h"
#include "ObjectManager.h"
#include "Prototype.h"
#include "ObjectFactory.h"
#include "ObjectPool.h"
#include "StageUI.h"

Stage::Stage() : pPlayer(nullptr), pUI(nullptr), _BackGround(nullptr), Check(0) { }
Stage::~Stage() { Release(); }


void Stage::Initialize()
{
	ObjectManager::GetInstance()->SetHp(3);

	Check = 0;

	pUI = new ScrollBox;
	pUI->Initialize();

	_BackGround = new BackGround;
	_BackGround->Initialize("BackGround");

	ObjectManager::GetInstance()->AddObject("Player");
	pPlayer = ObjectManager::GetInstance()->GetObjectList("Player")->front();

	Object* pEnemy = Prototype::GetInstance()->ProtoTypeObject("Enemy");
	Object* pEnemyBullet = Prototype::GetInstance()->ProtoTypeObject("EnemyBullet");

	for (int i = 0; i < 5; ++i)
	{
		srand(DWORD(GetTickCount64() * (i + 1)));

		pEnemy->SetPosition(float(rand() % 80 + (100 + (i * 20))), float(rand() % 30 + 10));

		for(int i = 0; i < 3; ++i)
			pEnemyBullet->SetPosition(pEnemy->GetPosition().x + i, pEnemy->GetPosition().y);

		ObjectManager::GetInstance()->AddObject("Enemy");
		ObjectManager::GetInstance()->AddObject("EnemyBullet");
	}
}

void Stage::Update()
{
	list<Object*>* pBulletList = ObjectManager::GetInstance()->GetObjectList("Bullet");
	list<Object*>* pEnemyList = ObjectManager::GetInstance()->GetObjectList("Enemy");
	list<Object*>* pEnemyBulletList = ObjectManager::GetInstance()->GetObjectList("EnemyBullet");

	DWORD dwKey = InputManager::GetInstance()->GetKey();

	if (dwKey & KEY_TAB)
	{
		Enable_UI();
	}

	if (dwKey & PRESS_0)
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
			if ((*iter)->GetPosition().x >= 179.0f)
			{
				//(*iter)->SetPosition((*iter)->GetPosition().x, (*iter)->GetPosition().y);
				iter = ObjectManager::GetInstance()->ThrowObject(iter, (*iter));
			}
			else
				++iter;
		}
	}

	if (pEnemyList != nullptr)
	{
		for (list<Object*>::iterator Enemyiter = pEnemyList->begin(); Enemyiter != pEnemyList->end();)
		{
			if (pEnemyBulletList != nullptr)
			{
				for (list<Object*>::iterator iter = pEnemyBulletList->begin(); iter != pEnemyBulletList->end();)
				{
					if ((*iter)->GetPosition().x <= 0.0f)
					{
						delete (*iter);
						iter = pEnemyBulletList->erase(iter);
					}
					else
						++iter;
				}
			}

			if ((*Enemyiter)->GetPosition().x <= -1.0f)
				Enemyiter = ObjectManager::GetInstance()->ThrowObject(Enemyiter, *Enemyiter);
			else
				++Enemyiter;
		}
	}

	if (pPlayer != nullptr)
	{
		if (pEnemyList != nullptr)
		{
			for (list<Object*>::iterator Enemyiter = pEnemyList->begin(); Enemyiter != pEnemyList->end();)
			{
				if (pBulletList != nullptr)
				{
					for (list<Object*>::iterator Bulletiter = pBulletList->begin(); Bulletiter != pBulletList->end();)
					{
						if (Enemyiter == pEnemyList->end())
							break;
						else if (CollisionManager::Collision(*Bulletiter, *Enemyiter))
						{
							delete (*Enemyiter);
							Enemyiter = pEnemyList->erase(Enemyiter);

							delete (*Bulletiter);
							Bulletiter = pBulletList->erase(Bulletiter);
						}
						else
							++Bulletiter;
					}
				}
				if (Enemyiter == pEnemyList->end())
					break;
				else
					++Enemyiter;
			}
		}
	}

	//if (pPlayer != nullptr)
	//{
	//	if (pEnemyList != nullptr)
	//	{
	//		for (list<Object*>::iterator Enemyiter = pEnemyList->begin(); Enemyiter != pEnemyList->end(); )
	//		{
	//			if (CollisionManager::Collision(pPlayer, *Enemyiter))
	//			{
	//				ObjectManager::GetInstance()->SubHp(1);
	//			}
	//			else
	//				++Enemyiter;
	//		}
	//	}
	//}

	if (Check)
		pUI->Update();
}

void Stage::Render()
{
	pPlayer->Render();

	ObjectManager::GetInstance()->Render();

	if (Check)
		pUI->Render();

	_BackGround->Render();

	//for (int i = 0; i < 30; ++i)
	//	CursorManager::GetInstance()->WriteBuffer(0.0f, 0.0f + i, (char*)" \n", 0);

	CursorManager::GetInstance()->WriteBuffer(1.0f, 0.0f, (char*)"HP : ");
	CursorManager::GetInstance()->WriteBuffer(6.0f, 0.0f, ObjectManager::GetInstance()->GetHp());

	CursorManager::GetInstance()->WriteBuffer(148.0f, 49.0f, (char*)"CREDIT : ", 14);
	CursorManager::GetInstance()->WriteBuffer(157.0f, 49.0f, ObjectManager::GetInstance()->GetCredit(), 14);
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
