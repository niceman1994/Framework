#include "Stage.h"
#include "StageUI.h"
#include "Player.h"
#include "Enemy.h"
#include "FrontShield.h"
#include "Item.h"
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

Stage::Stage() : pPlayer(nullptr), pFrontShield(nullptr), pUI(nullptr), _BackGround(nullptr), Check(0) { }
Stage::~Stage() { Release(); }

void Stage::Initialize()
{
	ObjectManager::GetInstance()->GetLife();
	ObjectManager::GetInstance()->GetStageScore();

	Check = 0;
	count = 0;

	pUI = new ScrollBox;
	pUI->Initialize();

	_BackGround = new BackGround;
	_BackGround->Initialize("BackGround");

	ObjectManager::GetInstance()->AddObject("Player");
	pPlayer = ObjectManager::GetInstance()->GetObjectList("Player")->front();

	ObjectManager::GetInstance()->AddObject("FrontShield");
	pFrontShield = ObjectManager::GetInstance()->GetObjectList("FrontShield")->front();

	Object* pEnemy = Prototype::GetInstance()->ProtoTypeObject("Enemy");
	Object* pEnemyBullet = Prototype::GetInstance()->ProtoTypeObject("EnemyBullet");

	for (int i = 0; i < 25; ++i)
	{
		srand(DWORD(GetTickCount64() * (i + 1)));

		pEnemy->SetPosition(float(rand() % 150 + (80 + (i * 30))), float(rand() % 30 + 10));
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
	//list<Object*>* pItemList = ObjectManager::GetInstance()->GetObjectList("Item");

	DWORD dwKey = InputManager::GetInstance()->GetKey();

	if (dwKey & KEY_TAB)
	{
		Enable_UI();
	}

	if (dwKey & KEY_0)
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
		if (pBulletList->size())
		{
			ObjectPool::GetInstance()->CatchObject(pBulletList->back());
			pBulletList->pop_back();
		}
	}

	if (pBulletList != nullptr)
	{
		for (list<Object*>::iterator Bulletiter = pBulletList->begin(); Bulletiter != pBulletList->end(); )
		{
			if ((*Bulletiter)->GetPosition().x >= 178.0f)
				Bulletiter = ObjectManager::GetInstance()->ThrowObject(Bulletiter, (*Bulletiter));
			else
				++Bulletiter;
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
		if (pEnemyList)
		{
			for (list<Object*>::iterator Enemyiter = pEnemyList->begin(); Enemyiter != pEnemyList->end();)
			{
				if (pBulletList)
				{
					for (list<Object*>::iterator Bulletiter = pBulletList->begin(); Bulletiter != pBulletList->end();)
					{
						if (Enemyiter == pEnemyList->end())
							break;
						if (CollisionManager::Collision(*Bulletiter, *Enemyiter))
						{
							ObjectManager::GetInstance()->AddScore(100);

							Object* pItem = Prototype::GetInstance()->ProtoTypeObject("Item");
							//pItem->SetPosition((*Enemyiter)->GetPosition());
							ObjectManager::GetInstance()->AddObject("Item");
							list<Object*>* pItemList = ObjectManager::GetInstance()->GetObjectList("Item");
							//list<Object*>::iterator Itemiter = pItemList->begin();

							for (list<Object*>::iterator Itemiter = pItemList->begin(); Itemiter != pItemList->end(); ++Itemiter)
								(*Itemiter)->SetPosition((*Enemyiter)->GetPosition());

							Enemyiter = ObjectManager::GetInstance()->ThrowObject(Enemyiter, *Enemyiter);
							Bulletiter = ObjectManager::GetInstance()->ThrowObject(Bulletiter, *Bulletiter);

							//if (Itemiter != pItemList->end())
							//	break;
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

		list<Object*>* pItemList = ObjectManager::GetInstance()->GetObjectList("Item");
		
		for (list<Object*>::iterator Itemiter = pItemList->begin(); Itemiter != pItemList->end();)
		{
			if (Itemiter == pItemList->end())
				break;
			if (CollisionManager::Collision(pPlayer, *Itemiter))
			{
				ObjectManager::GetInstance()->AddScore(500);
				Itemiter = ObjectManager::GetInstance()->ThrowObject(Itemiter, *Itemiter);
			}
			else if ((*Itemiter)->GetPosition().x <= 2.0f)
				Itemiter = ObjectManager::GetInstance()->ThrowObject(Itemiter, *Itemiter);
			else
				++Itemiter;
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
					ObjectManager::GetInstance()->SubLife(1);
					EnemyBulletiter = ObjectManager::GetInstance()->ThrowObject(EnemyBulletiter, *EnemyBulletiter);

					if (ObjectManager::GetInstance()->GetLife() == 0)
					{
						Sleep(100);
						pPlayer->Initialize("Player");
						ObjectManager::GetInstance()->SetLife(3);
					}
				}
				else
					++EnemyBulletiter;
			}
		}

		if (pFrontShield != nullptr)
		{
			if (pEnemyBulletList != nullptr)
			{
				for (list<Object*>::iterator EnemyBulletiter = pEnemyBulletList->begin(); EnemyBulletiter != pEnemyBulletList->end();)
				{
					if (CollisionManager::Collision(pFrontShield, *EnemyBulletiter))
						EnemyBulletiter = ObjectManager::GetInstance()->ThrowObject(EnemyBulletiter, *EnemyBulletiter);
					else
						++EnemyBulletiter;
				}
			}
		}
		//else
		//	pFrontShield->Initialize("FrontShield");
	}

	if (pEnemyList != nullptr)
	{
		for (list<Object*>::iterator Enemyiter = pEnemyList->begin(); Enemyiter != pEnemyList->end(); )
		{
			if (CollisionManager::CircleCollision(pPlayer, *Enemyiter))
			{
				ObjectManager::GetInstance()->SubLife(1);

				if (ObjectManager::GetInstance()->GetLife() == 0)
				{
					Sleep(100);
					pPlayer->Initialize("Player");
					ObjectManager::GetInstance()->SetLife(3);
				}

				pPlayer->Initialize("Player");
				Enemyiter = ObjectManager::GetInstance()->ThrowObject(Enemyiter, *Enemyiter);
			}
			else
				++Enemyiter;
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
	CursorManager::GetInstance()->WriteBuffer(6.0f, 0.0f, ObjectManager::GetInstance()->GetLife());

	CursorManager::GetInstance()->WriteBuffer(45.0f, 0.0f, (char*)"Score : ");
	CursorManager::GetInstance()->WriteBuffer(53.0f, 0.0f, ObjectManager::GetInstance()->GetStageScore());

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
