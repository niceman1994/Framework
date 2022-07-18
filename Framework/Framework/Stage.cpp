#include "Stage.h"
#include "StageUI.h"
#include "Player.h"
#include "Enemy.h"
#include "Enemy2.h"
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

Stage::Stage() : pPlayer(nullptr), pUI(nullptr), _BackGround(nullptr), Check(0) { }
Stage::~Stage() { Release(); }

void Stage::Initialize()
{
	ObjectManager::GetInstance()->GetHp();

	Check = 0;

	pUI = new ScrollBox;
	pUI->Initialize();

	_BackGround = new BackGround;
	_BackGround->Initialize("BackGround");

	ObjectManager::GetInstance()->AddObject("Player");
	pPlayer = ObjectManager::GetInstance()->GetObjectList("Player")->front();

	Object* pEnemy = Prototype::GetInstance()->ProtoTypeObject("Enemy");
	Object* pEnemyBullet = Prototype::GetInstance()->ProtoTypeObject("EnemyBullet");
	Object* pEnemy2 = Prototype::GetInstance()->ProtoTypeObject("Enemy2");
	pEnemy2->SetPosition(80.0f, 48.0f);
	ObjectManager::GetInstance()->AddObject("Enemy2");

	for (int i = 0; i < 10; ++i)
	{
		srand(DWORD(GetTickCount64() * (i + 1)));

		pEnemy->SetPosition(float(rand() % 100 + (80 + (i * 30))), float(rand() % 30 + 10));
		pEnemyBullet->SetPosition(pEnemy->GetPosition().x, pEnemy->GetPosition().y);
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
		else if (pBulletList->size() < 10 && pBulletList->size() >= 5)
		{
			for (int i = 0; i < 10; ++i)
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
		for (list<Object*>::iterator iter = pBulletList->begin(); iter != pBulletList->end(); )
		{
			if ((*iter)->GetPosition().x >= 179.0f)
				iter = ObjectManager::GetInstance()->ThrowObject(iter, (*iter));
			else
				++iter;
		}
	}

	if (pEnemyBulletList != nullptr)
	{
		for (list<Object*>::iterator iter = pEnemyBulletList->begin(); iter != pEnemyBulletList->end();)
		{
			if ((*iter)->GetPosition().x <= 0.0f)
				iter = ObjectManager::GetInstance()->ThrowObject(iter, (*iter));
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
						iter = ObjectManager::GetInstance()->ThrowObject(iter, (*iter));
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

	if (pPlayer != nullptr)
	{
		if (pEnemyBulletList != nullptr)
		{
			for (list<Object*>::iterator EnemyBulletiter = pEnemyBulletList->begin(); EnemyBulletiter != pEnemyBulletList->end();)
			{
				if (CollisionManager::Collision(pPlayer, *EnemyBulletiter))
				{
					ObjectManager::GetInstance()->SubHp(1);
					EnemyBulletiter = ObjectManager::GetInstance()->ThrowObject(EnemyBulletiter, *EnemyBulletiter);

					if (ObjectManager::GetInstance()->GetHp() == 0)
					{
						Sleep(100);
						pPlayer->Initialize("Player");
						ObjectManager::GetInstance()->SetHp(3);
					}
				}
				else
					++EnemyBulletiter;
			}
		}

		if (pEnemyList != nullptr)
		{
			for (list<Object*>::iterator Enemyiter = pEnemyList->begin(); Enemyiter != pEnemyList->end(); )
			{
				if (CollisionManager::CircleCollision(pPlayer, *Enemyiter))
				{
					ObjectManager::GetInstance()->SubHp(1);

					if (ObjectManager::GetInstance()->GetHp() == 0)
					{
						Sleep(100);
						pPlayer->Initialize("Player");
						ObjectManager::GetInstance()->SetHp(3);
					}

					pPlayer->Initialize("Player");
					Enemyiter = ObjectManager::GetInstance()->ThrowObject(Enemyiter, *Enemyiter);
				}
				else
					++Enemyiter;
			}
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

	_BackGround->Render();

	CursorManager::GetInstance()->WriteBuffer(1.0f, 0.0f, (char*)"HP : ");
	CursorManager::GetInstance()->WriteBuffer(6.0f, 0.0f, ObjectManager::GetInstance()->GetHp());

	CursorManager::GetInstance()->WriteBuffer(152.0f, 49.0f, (char*)"CREDIT : ", 14);
	CursorManager::GetInstance()->WriteBuffer(161.0f, 49.0f, ObjectManager::GetInstance()->GetCredit(), 14);
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
