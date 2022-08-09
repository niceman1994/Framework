#include "Stage_1.h"
#include "Player.h"

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

#include "FlyingEnemy.h"
#include "RushingEnemy.h"
#include "BossParts_Body.h"
#include "BossParts_LeftArms.h"
#include "BossParts_RightArms.h"
#include "ScoreItem.h"
#include "ShieldItem.h"
#include "LifeUpItem.h"
#include "FrontShield.h"

Stage_1::Stage_1() : pPlayer(nullptr), pFrontShield(nullptr), pBoss(nullptr), TextureList() { }
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

	count = 0;

	if (pPlayer == nullptr)
	{
		ObjectManager::GetInstance()->AddObject("Player");
		pPlayer = ObjectManager::GetInstance()->GetObjectList("Player")->front();
	}

	Object* pEnemy = Prototype::GetInstance()->ProtoTypeObject("Enemy");
	Object* pEnemyBullet = Prototype::GetInstance()->ProtoTypeObject("EnemyBullet");

	{
		Bridge* pBridge1 = new BossParts_Body;
		Bridge* pBridge2 = new BossParts_RightArms;
		Bridge* pBridge3 = new BossParts_LeftArms;
		
		pBoss = Prototype::GetInstance()->ProtoTypeObject("Boss");
		pBoss->SetPosition(200.0f, 25.0f);

		ObjectManager::GetInstance()->AddObject("Boss", pBridge1, pBoss->GetPosition());
		ObjectManager::GetInstance()->AddObject("Boss", pBridge2, pBoss->GetPosition().x, pBoss->GetPosition().y - 5.0f);
		ObjectManager::GetInstance()->AddObject("Boss", pBridge3, pBoss->GetPosition().x, pBoss->GetPosition().y + 5.0f);
	}

	//for (int i = 0; i < 20; ++i)
	//{
	//	srand(DWORD(GetTickCount64() * (i + 1)));
	//
	//	Bridge* pBridge = new FlyingEnemy;
	//	pEnemy->SetPosition(float(rand() % 150 + (80 + (i * 30))), float(rand() % 30 + 10));
	//	pEnemyBullet->SetPosition(pEnemy->GetPosition().x, pEnemy->GetPosition().y);
	//	ObjectManager::GetInstance()->AddObject("Enemy", pBridge, pEnemy->GetPosition());
	//	ObjectManager::GetInstance()->AddObject("EnemyBullet");
	//}
}

void Stage_1::CreateEnemy()
{
	if (rand() % 50 == 25 && ScoreManager::GetInstance()->GetStageScore() <= 2000)
	{
		Object* pEnemy = Prototype::GetInstance()->ProtoTypeObject("Enemy");

		for (int i = 0; i < 6; ++i)
		{
			Bridge* pBridge = new RushingEnemy;
			pEnemy->SetPosition(400.0f + (i * 10), 25.0f - (i * 3));
			ObjectManager::GetInstance()->AddObject("Enemy", pBridge, pEnemy->GetPosition());
		}

		for (int i = 6; i < 11; ++i)
		{
			Bridge* pBridge = new RushingEnemy;
			pEnemy->SetPosition(350.0f + (i * 10), 10.0f + (i * 3));
			ObjectManager::GetInstance()->AddObject("Enemy", pBridge, pEnemy->GetPosition());
		}
	}
}

void Stage_1::MoveBoss()
{
	if (pBoss->GetPosition().x == 150.0f)
	{
		pBoss->SetPosition(pBoss->GetPosition().x, pBoss->GetPosition().y - 1.0f);

		if (pBoss->GetPosition().y <= 15.0f)
			return;
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

							if (rand() % 30 == 1 || rand() % 30 == 2 || rand() % 30 == 3 || rand() % 30 == 4)
							{
								Bridge* pBridge = new ScoreItem;
								ObjectManager::GetInstance()->AddObject("Item", pBridge, (*Enemyiter)->GetPosition());
							}
							else if (rand() % 30 == 5 || rand() % 30 == 6)
							{
								Bridge* pBridge = new ShieldItem;
								ObjectManager::GetInstance()->AddObject("Item", pBridge, (*Enemyiter)->GetPosition());
							}
							else if (rand() % 100 == 10)
							{
								Bridge* pBridge = new LifeUpItem;
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
				ObjectManager::GetInstance()->AddPlayerHitCount(1);

				if(ObjectManager::GetInstance()->GetPlayerHitCount())
					_Object->Initialize("Player");

				Scene::PlayerLifeState();
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

void Stage_1::FrontShieldCollision(Object* _Object, list<Object*>* _Objectlist)
{
	if (_Object != nullptr)
	{
		if (_Objectlist != nullptr)
		{
			for (list<Object*>::iterator EnemyBulletiter = _Objectlist->begin(); EnemyBulletiter != _Objectlist->end();)
			{
				if (CollisionManager::Collision(_Object, *EnemyBulletiter))
					EnemyBulletiter = ObjectManager::GetInstance()->ThrowObject(EnemyBulletiter, *EnemyBulletiter);
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
						else if (CollisionManager::Collision(*Bulletiter, *Bossiter))
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

void Stage_1::PlayerBossCollision(Object* _Object, list<Object*>* _Objectlist)
{
	if (_Objectlist != nullptr)
	{
		for (list<Object*>::iterator Bossiter = _Objectlist->begin(); Bossiter != _Objectlist->end(); )
		{
			if (CollisionManager::Collision(_Object, *Bossiter))
			{
				ObjectManager::GetInstance()->AddPlayerHitCount(1);

				if (ObjectManager::GetInstance()->GetPlayerHitCount())
					_Object->Initialize("Player");

				Scene::PlayerLifeState();
			}
			else
				++Bossiter;
		}
	}
}

void Stage_1::BulletToBulletCollision(Object* _Object, list<Object*>* _ObjectlistA, list<Object*>* _ObjectlistB)
{
	if (_Object != nullptr)
	{
		if (_ObjectlistA != nullptr)
		{
			for (list<Object*>::iterator Bulletiter = _ObjectlistA->begin(); Bulletiter != _ObjectlistA->end();)
			{
				if (_ObjectlistB != nullptr)
				{
					for (list<Object*>::iterator EnemyBulletiter = _ObjectlistB->begin(); EnemyBulletiter != _ObjectlistB->end();)
					{
						if (Bulletiter == _ObjectlistA->end())
							break;
						else if (CollisionManager::Collision(*Bulletiter, *EnemyBulletiter) && (*EnemyBulletiter)->GetBridgeName() == "BossSpecialBullet")
							EnemyBulletiter = ObjectManager::GetInstance()->ThrowObject(EnemyBulletiter, *EnemyBulletiter);
						else
							++EnemyBulletiter;
					}
				}
				if (Bulletiter == _ObjectlistA->end())
					break;
				else
					++Bulletiter;
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

	//CreateEnemy();
	//MoveBoss();

	DWORD dwKey = InputManager::GetInstance()->GetKey();

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
				else if ((*Itemiter)->GetBridgeName() == "LifeUpItem")
				{
					ObjectManager::GetInstance()->SubtractPlayerHitCount(1);
					Scene::PlayerLifeState();

					if ((ObjectManager::GetInstance()->GetPlayerHitCount() == 0 || ObjectManager::GetInstance()->GetPlayerHitCount() == 4)
						&& CollisionManager::Collision(pPlayer, (*Itemiter)))
						ScoreManager::GetInstance()->AddScore(1000);
				}
				Itemiter = ObjectManager::GetInstance()->ThrowObject(Itemiter, *Itemiter);
			}
			else if ((*Itemiter)->GetPosition().x <= 2.0f)
				Itemiter = ObjectManager::GetInstance()->ThrowObject(Itemiter, *Itemiter);
			else
				++Itemiter;
		}

		FrontShieldCollision(pFrontShield, pEnemyBulletList);
	}

	BossCollision(pPlayer, pBossList, pBulletList);
	BulletToBulletCollision(pPlayer, pBulletList, pEnemyBulletList);
	PlayerBossCollision(pPlayer, pBossList);

	Scene::ObjectPassBy(pBossList, pEnemyBulletList);

	EnemyBulletCollision(pPlayer, pEnemyBulletList);

	if (pBossList->empty())
		SceneManager::GetInstance()->SetScene(STAGE_CLEAR);
}

void Stage_1::Render()
{
	pPlayer->Render();

	ObjectManager::GetInstance()->Render();

	CursorManager::GetInstance()->WriteBuffer(1.0f, 0.0f, (char*)"HP [");
	CursorManager::GetInstance()->WriteBuffer(6.0f, 0.0f, ObjectManager::GetInstance()->LifeState());
	CursorManager::GetInstance()->WriteBuffer(15.0f, 0.0f, (char*)"]");

	CursorManager::GetInstance()->WriteBuffer(80.0f, 0.0f, (char*)"Score : ");
	CursorManager::GetInstance()->WriteBuffer(88.0f, 0.0f, ScoreManager::GetInstance()->GetStageScore());

	CursorManager::GetInstance()->WriteBuffer(152.0f, 49.0f, (char*)"CREDIT : ", 14);
	CursorManager::GetInstance()->WriteBuffer(161.0f, 49.0f, ScoreManager::GetInstance()->GetCredit(), 14);

	CursorManager::GetInstance()->WriteBuffer(0.0f, 1.0f, TextureList[0]);
	CursorManager::GetInstance()->WriteBuffer(0.0f, 48.0f, TextureList[1]);
}

void Stage_1::Release()
{
	delete pPlayer;
	pPlayer = nullptr;
}
