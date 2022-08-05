#include "Stage_1.h"
#include "Player.h"
#include "FlyingEnemy.h"
#include "BossParts_Body.h"

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

#include "ScoreItem.h"
#include "ShieldItem.h"
#include "LifeUpItem.h"
#include "FrontShield.h"

Stage_1::Stage_1() : pPlayer(nullptr), pFrontShield(nullptr), pUI(nullptr), TextureList(), Check(0) { }
Stage_1::~Stage_1() { Release(); }

void Stage_1::Initialize()
{
	ObjectManager::GetInstance()->LifeState();
	ScoreManager::GetInstance()->GetStageScore();
	ObjectManager::GetInstance()->GetHitCount();
	ObjectManager::GetInstance()->GetPlayerHitCount();

	TextureList[0] = (char*)
		"£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß";

	TextureList[1] = (char*)
		"£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ";

	Check = 0;
	count = 0;

	pUI = new ScrollBox;
	pUI->Initialize();

	ObjectManager::GetInstance()->AddObject("Player");
	pPlayer = ObjectManager::GetInstance()->GetObjectList("Player")->front();

	Object* pEnemy = Prototype::GetInstance()->ProtoTypeObject("Enemy");
	Object* pEnemyBullet = Prototype::GetInstance()->ProtoTypeObject("EnemyBullet");

	Bridge* pBridge = new BossParts_Body;
	pBridge->GetBridgeKey();
	Object* pBoss = Prototype::GetInstance()->ProtoTypeObject("Boss");
	pBoss->SetPosition(200.0f, 25.0f);
	ObjectManager::GetInstance()->AddObject("Boss", pBridge, pBoss->GetPosition()); 

	//for (int i = 0; i < 20; ++i)
	//{
	//	srand(DWORD(GetTickCount64() * (i + 1)));
	//
	//	Bridge* pBridge = new FlyingEnemy;
	//	pBridge->GetBridgeKey();
	//	pEnemy->SetPosition(float(rand() % 150 + (80 + (i * 30))), float(rand() % 30 + 10));
	//	pEnemyBullet->SetPosition(pEnemy->GetPosition().x, pEnemy->GetPosition().y);
	//	ObjectManager::GetInstance()->AddObject("Enemy", pBridge, pEnemy->GetPosition());
	//	ObjectManager::GetInstance()->AddObject("EnemyBullet");
	//}
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
							else if (rand() % 100 == 10)
							{
								Bridge* pBridge = new LifeUpItem;
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

void Stage_1::GetItem(Object* _ObjectA, Object* _ObjectB, list<Object*>* _ObjectlistA, list<Object*>* _ObjectlistB)
{
	if (_ObjectA != nullptr)
	{
		for (list<Object*>::iterator Itemiter = _ObjectlistA->begin(); Itemiter != _ObjectlistA->end();)
		{
			if (Itemiter == _ObjectlistA->end())
				break;
			if (CollisionManager::Collision(_ObjectA, (*Itemiter)))
			{
				if ((*Itemiter)->GetBridgeName() == "ScoreItem")
					ScoreManager::GetInstance()->AddScore(400);
				else if ((*Itemiter)->GetBridgeName() == "ShieldItem")
				{
					if (_ObjectB != nullptr && CollisionManager::Collision(_ObjectA, (*Itemiter)))
					{
						Itemiter = ObjectManager::GetInstance()->ThrowObject(Itemiter, *Itemiter);
						ScoreManager::GetInstance()->AddScore(200);
						break;
					}

					ObjectManager::GetInstance()->AddObject("FrontShield");
					_ObjectB = ObjectManager::GetInstance()->GetObjectList("FrontShield")->front();
					_ObjectB->Initialize("FrontShield");
				}
				else if ((*Itemiter)->GetBridgeName() == "LifeUpItem")
				{
					ObjectManager::GetInstance()->SubtractPlayerHitCount(1);
					Scene::PlayerLifeState();

					if ((ObjectManager::GetInstance()->GetPlayerHitCount() == 0 || ObjectManager::GetInstance()->GetPlayerHitCount() == 4)
						&& CollisionManager::Collision(_ObjectA, (*Itemiter)))
						ScoreManager::GetInstance()->AddScore(1000);
				}
				Itemiter = ObjectManager::GetInstance()->ThrowObject(Itemiter, *Itemiter);
			}
			else if ((*Itemiter)->GetPosition().x <= 2.0f)
				Itemiter = ObjectManager::GetInstance()->ThrowObject(Itemiter, *Itemiter);
			else
				++Itemiter;
		}

		if (_ObjectB != nullptr)
		{
			if (_ObjectlistB != nullptr)
			{
				for (list<Object*>::iterator EnemyBulletiter = _ObjectlistB->begin(); EnemyBulletiter != _ObjectlistB->end();)
				{
					if (CollisionManager::Collision(_ObjectB, *EnemyBulletiter))
						EnemyBulletiter = ObjectManager::GetInstance()->ThrowObject(EnemyBulletiter, *EnemyBulletiter);
					else
						++EnemyBulletiter;
				}
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
				ObjectManager::GetInstance()->AddPlayerHitCount(1);
				Scene::PlayerLifeState();

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
					ObjectManager::GetInstance()->AddPlayerHitCount(1);
					Scene::PlayerLifeState();

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

	GetItem(pPlayer, pFrontShield, pItemList, pEnemyBulletList);

	BossCollision(pPlayer, pBossList, pBulletList);

	Scene::ObjectPassBy(pBossList, pEnemyBulletList);

	EnemyBulletCollision(pPlayer, pEnemyBulletList);

	if (Check)
		pUI->Update();
}

void Stage_1::Render()
{
	pPlayer->Render();

	ObjectManager::GetInstance()->Render();

	if (Check)
		pUI->Render();

	CursorManager::GetInstance()->WriteBuffer(1.0f, 0.0f, (char*)"HP [");
	CursorManager::GetInstance()->WriteBuffer(6.0f, 0.0f, ObjectManager::GetInstance()->LifeState());
	CursorManager::GetInstance()->WriteBuffer(15.0f, 0.0f, (char*)"]");

	CursorManager::GetInstance()->WriteBuffer(45.0f, 0.0f, (char*)"Score : ");
	CursorManager::GetInstance()->WriteBuffer(53.0f, 0.0f, ScoreManager::GetInstance()->GetStageScore());

	CursorManager::GetInstance()->WriteBuffer(152.0f, 49.0f, (char*)"CREDIT : ", 14);
	CursorManager::GetInstance()->WriteBuffer(161.0f, 49.0f, ScoreManager::GetInstance()->GetCredit(), 14);

	CursorManager::GetInstance()->WriteBuffer(0.0f, 1.0f, TextureList[0]);
	CursorManager::GetInstance()->WriteBuffer(0.0f, 48.0f, TextureList[1]);
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
