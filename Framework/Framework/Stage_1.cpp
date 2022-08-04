#include "Stage_1.h"
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"

#include "ScrollBox.h"

#include "SceneManager.h"
#include "CollisionManager.h"
#include "InputManager.h"
#include "CursorManager.h"
#include "ObjectManager.h"
#include "ScoreManager.h"
#include "ObjectPool.h"

#include "Prototype.h"
#include "ObjectFactory.h"

#include "Item.h"
#include "ScoreItem.h"
#include "ShieldItem.h"
#include "FrontShield.h"
#include "BackGround.h"

Stage_1::Stage_1() : pPlayer(nullptr), pFrontShield(nullptr), LifeItem(nullptr), pUI(nullptr), _BackGround(nullptr), Check(0) { }
Stage_1::~Stage_1() { Release(); }

void Stage_1::Initialize()
{
	ScoreManager::GetInstance()->GetLife();
	ScoreManager::GetInstance()->GetStageScore();
	ObjectManager::GetInstance()->GetHitCount();

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

	Object* pBoss = Prototype::GetInstance()->ProtoTypeObject("Boss");
	ObjectManager::GetInstance()->AddObject("Boss");

	for (int i = 0; i < 15; ++i)
	{
		srand(DWORD(GetTickCount64() * (i + 1)));
	
		pEnemy->SetPosition(float(rand() % 150 + (80 + (i * 30))), float(rand() % 30 + 10));
		pEnemyBullet->SetPosition(pEnemy->GetPosition().x, pEnemy->GetPosition().y);
		ObjectManager::GetInstance()->AddObject("Enemy");
		ObjectManager::GetInstance()->AddObject("EnemyBullet");
	}
}

void Stage_1::CreateItem(Object* _Object, list<Object*>* _ObjectlistA, list<Object*>* _ObjectlistB)
{
	if (_Object != nullptr)
	{
		if (_ObjectlistA)
		{
			for (list<Object*>::iterator Enemyiter = _ObjectlistA->begin(); Enemyiter != _ObjectlistA->end();)
			{
				if (_ObjectlistB)
				{
					for (list<Object*>::iterator Bulletiter = _ObjectlistB->begin(); Bulletiter != _ObjectlistB->end();)
					{
						if (Enemyiter == _ObjectlistA->end())
							break;
						if (CollisionManager::Collision(*Bulletiter, *Enemyiter))
						{
							ScoreManager::GetInstance()->AddScore(100);

							if (rand() % 20 == 1 || rand() % 20 == 3 || rand() % 20 == 4 || rand() % 20 == 5)
							{
								Bridge* pBridge = new ScoreItem;
								pBridge->GetBridgeKey();
								ObjectManager::GetInstance()->AddObject("Item", pBridge, (*Enemyiter)->GetPosition());
							}
							else if (rand() % 20 == 2)
							{
								Bridge* pBridge = new ShieldItem;
								pBridge->GetBridgeKey();
								ObjectManager::GetInstance()->AddObject("Item", pBridge, (*Enemyiter)->GetPosition());
							}
							list<Object*>* pItemList = ObjectManager::GetInstance()->GetObjectList("Item");

							Enemyiter = ObjectManager::GetInstance()->ThrowObject(Enemyiter, *Enemyiter);
							Bulletiter = ObjectManager::GetInstance()->ThrowObject(Bulletiter, *Bulletiter);
						}
						else
							++Bulletiter;
					}
				}
				if (Enemyiter == _ObjectlistA->end())
					break;
				else
					++Enemyiter;
			}
		}
	}
}

void Stage_1::PlayerCollision(Object* _Object, list<Object*>* _Objectlist)
{
	if (_Objectlist != nullptr)
	{
		for (list<Object*>::iterator Enemyiter = _Objectlist->begin(); Enemyiter != _Objectlist->end(); )
		{
			if (CollisionManager::CircleCollision(_Object, *Enemyiter))
			{
				ScoreManager::GetInstance()->SubtractLife();

				if (ScoreManager::GetInstance()->GetLife()[8])
				{
					Sleep(100);
					_Object->Initialize("Player");
					ScoreManager::GetInstance()->SetLife((char*)"¡á¡á¡á¡á");
				}

				_Object->Initialize("Player");
				Enemyiter = ObjectManager::GetInstance()->ThrowObject(Enemyiter, *Enemyiter);
			}
			else
				++Enemyiter;
		}
	}
}

void Stage_1::EnemyBulletCollision(Object* _Object, list<Object*>* _Objectlist)
{
	if (_Object != nullptr)
	{
		if (_Objectlist != nullptr)
		{
			for (list<Object*>::iterator EnemyBulletiter = _Objectlist->begin(); EnemyBulletiter != _Objectlist->end();)
			{
				if (CollisionManager::Collision(_Object, *EnemyBulletiter))
				{
					ScoreManager::GetInstance()->SubtractLife();

					if (ScoreManager::GetInstance()->GetLife()[8])
					{
						Sleep(100);
						_Object->Initialize("Player");
						ScoreManager::GetInstance()->SetLife((char*)"¡á¡á¡á¡á");
					}

					EnemyBulletiter = ObjectManager::GetInstance()->ThrowObject(EnemyBulletiter, *EnemyBulletiter);
				}
				else
					++EnemyBulletiter;
			}
		}
	}
}

void Stage_1::BossCollision(Object* _Object, list<Object*>* _ObjectlistA, list<Object*>* _ObjectlistB)
{
	if (_Object != nullptr)
	{
		if (_ObjectlistA != nullptr)
		{
			for (list<Object*>::iterator Bossiter = _ObjectlistA->begin(); Bossiter != _ObjectlistA->end();)
			{
				if (_ObjectlistB != nullptr)
				{
					for (list<Object*>::iterator Bulletiter = _ObjectlistB->begin(); Bulletiter != _ObjectlistB->end();)
					{
						if (Bossiter == _ObjectlistA->end())
							break;
						else if (CollisionManager::BossCollision(*Bulletiter, *Bossiter))
						{
							ObjectManager::GetInstance()->AddHitCount(1);
							Bulletiter = ObjectManager::GetInstance()->ThrowObject(Bulletiter, *Bulletiter);

							if (ObjectManager::GetInstance()->GetHitCount() == 50)
							{
								ScoreManager::GetInstance()->AddScore(2000);
								Bossiter = ObjectManager::GetInstance()->ThrowObject(Bossiter, *Bossiter);
								ObjectManager::GetInstance()->ResetHitCount();
							}
						}
						else
							++Bulletiter;
					}
				}
				if (Bossiter == _ObjectlistA->end())
					break;
				else
					++Bossiter;
			}
		}
	}
}

void Stage_1::Update()
{
	list<Object*>* pBulletList = ObjectManager::GetInstance()->GetObjectList("Bullet");
	list<Object*>* pEnemyList = ObjectManager::GetInstance()->GetObjectList("Enemy");
	list<Object*>* pEnemyBulletList = ObjectManager::GetInstance()->GetObjectList("EnemyBullet");
	list<Object*>* pBossList = ObjectManager::GetInstance()->GetObjectList("Boss");

	DWORD dwKey = InputManager::GetInstance()->GetKey();

	if (dwKey & KEY_TAB)
		Enable_UI();

	if (dwKey & KEY_0)
	{
		ScoreManager::GetInstance()->IncreaseCredit();
		CursorManager::GetInstance()->ClearBuffer();
		Sleep(100);

		if (ScoreManager::GetInstance()->GetCredit() >= 99)
			ScoreManager::GetInstance()->SetCredit(99);
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

	Scene::BulletPassBy(pBulletList);

	Scene::EnemyBulletPassBy(pEnemyBulletList);

	Scene::ObjectPassBy(pEnemyList, pEnemyBulletList);

	CreateItem(pPlayer, pEnemyList, pBulletList);

	PlayerCollision(pPlayer, pEnemyList);

	Scene::ObjectPassBy(pBossList, pEnemyBulletList);

	list<Object*>* pItemList = ObjectManager::GetInstance()->GetObjectList("Item");

	if (pPlayer != nullptr)
	{
		for (list<Object*>::iterator Itemiter = pItemList->begin(); Itemiter != pItemList->end();)
		{
			if (Itemiter == pItemList->end())
				break;
			if (CollisionManager::Collision(pPlayer, (*Itemiter)))
			{
				if ((*Itemiter)->GetBridgeName() == "ScoreItem")
					ScoreManager::GetInstance()->AddScore(400);
				else if ((*Itemiter)->GetBridgeName() == "ShieldItem")
				{
					if (pFrontShield != nullptr && CollisionManager::Collision(pPlayer, (*Itemiter)))
					{
						Itemiter = ObjectManager::GetInstance()->ThrowObject(Itemiter, *Itemiter);
						ScoreManager::GetInstance()->AddScore(200);
						break;
					}

					ObjectManager::GetInstance()->AddObject("FrontShield");
					pFrontShield = ObjectManager::GetInstance()->GetObjectList("FrontShield")->front();
					pFrontShield->Initialize("FrontShield");
				}
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

	BossCollision(pPlayer, pBossList, pBulletList);

	Scene::ObjectPassBy(pBossList, pEnemyBulletList);

	EnemyBulletCollision(pPlayer, pEnemyBulletList);

	if (Check)
		pUI->Update();

	if (_BackGround)
		_BackGround->Update();
}

void Stage_1::Render()
{
	pPlayer->Render();

	ObjectManager::GetInstance()->Render();

	if (Check)
		pUI->Render();

	_BackGround->Render();

	CursorManager::GetInstance()->WriteBuffer(1.0f, 0.0f, (char*)"HP [");
	CursorManager::GetInstance()->WriteBuffer(6.0f, 0.0f, ScoreManager::GetInstance()->GetLife());
	CursorManager::GetInstance()->WriteBuffer(15.0f, 0.0f, (char*)"]");

	CursorManager::GetInstance()->WriteBuffer(45.0f, 0.0f, (char*)"Score : ");
	CursorManager::GetInstance()->WriteBuffer(53.0f, 0.0f, ScoreManager::GetInstance()->GetStageScore());

	CursorManager::GetInstance()->WriteBuffer(152.0f, 49.0f, (char*)"CREDIT : ", 14);
	CursorManager::GetInstance()->WriteBuffer(161.0f, 49.0f, ScoreManager::GetInstance()->GetCredit(), 14);
}

void Stage_1::Release()
{
	//delete pPlayer;
	//pPlayer = nullptr;
}

void Stage_1::Enable_UI()
{
	Check = !Check;
}
