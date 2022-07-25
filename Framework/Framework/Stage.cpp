#include "Stage.h"
#include "StageUI.h"
#include "Player.h"
#include "Enemy.h"

#include "ScrollBox.h"

#include "SceneManager.h"
#include "CollisionManager.h"
#include "InputManager.h"
#include "CursorManager.h"
#include "ObjectManager.h"
#include "ObjectPool.h"

#include "Prototype.h"
#include "ObjectFactory.h"

#include "ScoreItem.h"
#include "ShieldItem.h"
#include "LifeItem.h"
#include "FrontShield.h"
#include "Item.h"
#include "BackGround.h"

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

	Scene::Collsion(pBulletList);
	//if (pBulletList != nullptr)
	//{
	//	for (list<Object*>::iterator Bulletiter = pBulletList->begin(); Bulletiter != pBulletList->end(); )
	//	{
	//		if ((*Bulletiter)->GetPosition().x >= 178.0f)
	//			Bulletiter = ObjectManager::GetInstance()->ThrowObject(Bulletiter, (*Bulletiter));
	//		else
	//			++Bulletiter;
	//	}
	//}

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

							if (rand() % 10 == 1 || rand() % 10 == 3 || rand() % 10 == 4 || rand() % 10 == 5)
							{
								Bridge* pBridge = new ScoreItem;
								pBridge->GetBridgeKey();
								ObjectManager::GetInstance()->AddObject("Item", pBridge, (*Enemyiter)->GetPosition());
							}
							else if (rand() % 10 == 2)
							{
								Bridge* pBridge = new ShieldItem;
								pBridge->GetBridgeKey();
								ObjectManager::GetInstance()->AddObject("Item", pBridge, (*Enemyiter)->GetPosition());
							}
							list<Object*>* pItemList = ObjectManager::GetInstance()->GetObjectList("Item");
							//if (rand() % 200 == 1)
							//{
							//	Bridge* pBridge = new LifeItem;
							//	pBridge->GetBridgeKey();
							//	ObjectManager::GetInstance()->AddObject("Item", pBridge, (*Enemyiter)->GetPosition());
							//	list<Object*>* pItemList = ObjectManager::GetInstance()->GetObjectList("Item");
							//}

							Enemyiter = ObjectManager::GetInstance()->ThrowObject(Enemyiter, *Enemyiter);
							Bulletiter = ObjectManager::GetInstance()->ThrowObject(Bulletiter, *Bulletiter);
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
					ObjectManager::GetInstance()->SubtractLife();

					if (ObjectManager::GetInstance()->GetLife()[8])
					{
						Sleep(100);
						pPlayer->Initialize("Player");
						ObjectManager::GetInstance()->SetLife((char*)"¡á¡á¡á¡á");
					}

					EnemyBulletiter = ObjectManager::GetInstance()->ThrowObject(EnemyBulletiter, *EnemyBulletiter);
				}
				else
					++EnemyBulletiter;
			}
		}

		list<Object*>* pItemList = ObjectManager::GetInstance()->GetObjectList("Item");

		for (list<Object*>::iterator Itemiter = pItemList->begin(); Itemiter != pItemList->end();)
		{
			if (Itemiter == pItemList->end())
				break;
			if (CollisionManager::Collision(pPlayer, (*Itemiter)))
			{	
				if ((*Itemiter)->GetBridgeName() == "ScoreItem")
					ObjectManager::GetInstance()->AddScore(400);
				else if ((*Itemiter)->GetBridgeName() == "ShieldItem")
				{
					if (pFrontShield != nullptr && CollisionManager::Collision(pPlayer, (*Itemiter)))
					{
						Itemiter = ObjectManager::GetInstance()->ThrowObject(Itemiter, *Itemiter);
						ObjectManager::GetInstance()->AddScore(200);
						break;
					}

					ObjectManager::GetInstance()->AddObject("FrontShield");
					pFrontShield = ObjectManager::GetInstance()->GetObjectList("FrontShield")->front();
					pFrontShield->Initialize("FrontShield");
				}
				//else if ((*Itemiter)->GetBridgeName() == "LifeItem")
				//{
				//	
				//}

				Itemiter = ObjectManager::GetInstance()->ThrowObject(Itemiter, *Itemiter);
			}
			else if ((*Itemiter)->GetPosition().x <= 2.0f)
				Itemiter = ObjectManager::GetInstance()->ThrowObject(Itemiter, *Itemiter);
			else
				++Itemiter;
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
	}

	if (pEnemyList != nullptr)
	{
		for (list<Object*>::iterator Enemyiter = pEnemyList->begin(); Enemyiter != pEnemyList->end(); )
		{
			if (CollisionManager::CircleCollision(pPlayer, *Enemyiter))
			{
				ObjectManager::GetInstance()->SubtractLife();

				if (ObjectManager::GetInstance()->GetLife()[8])
				{
					Sleep(100);
					pPlayer->Initialize("Player");
					ObjectManager::GetInstance()->SetLife((char*)"¡á¡á¡á¡á");
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

	CursorManager::GetInstance()->WriteBuffer(0.0f, 0.0f, (char*)"HP [");
	CursorManager::GetInstance()->WriteBuffer(5.0f, 0.0f, ObjectManager::GetInstance()->GetLife());
	CursorManager::GetInstance()->WriteBuffer(14.0f, 0.0f, (char*)"]");

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
