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
#include "ObjectPool.h"

Stage::Stage() : Check(0) { }
Stage::~Stage() { Release(); }


void Stage::Initialize()
{
	Check = 0;

	pUI = new ScrollBox;
	pUI->Initialize();

	pPlayer = Prototype::GetInstance()->ProtoTypeObject("Player");
	ObjectManager::GetInstance()->AddObject("Player");
	
	Object* pEnemy = Prototype::GetInstance()->ProtoTypeObject("Enemy");

	for (int i = 0; i < 5; ++i)
	{
		srand(DWORD(GetTickCount64() * (i + 1)));

		pEnemy->SetPosition(float(rand() % 118), float(rand() % 25));
		ObjectManager::GetInstance()->AddObject("Enemy");
	}
}

void Stage::Update()
{
	DWORD dwKey = InputManager::GetInstance()->GetKey();

	/*if (dwKey & KEY_ESCAPE)
	{
		while (true)
		{
			if (Check == 1)
			{
				Scene::PauseMessage();
				system("pause");
				break;
			}
			else
				break;
		}
	}*/

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
	
	//Object* pPlayer = ObjectManager::GetInstance()->GetObjectList("Player")->front();
	list<Object*>* pBulletList = ObjectManager::GetInstance()->GetObjectList("Bullet");
	list<Object*>* pEnemyList = ObjectManager::GetInstance()->GetObjectList("Enemy");

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
		for (list<Object*>::iterator iter = pBulletList->begin();
			iter != pBulletList->end(); )
		{
			if ((*iter)->GetPosition().x >= 120.0f)
				iter = pBulletList->erase(iter);
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
					Enemyiter = ObjectManager::GetInstance()->ThrowObject(Enemyiter, (*Enemyiter));

				if (pBulletList != nullptr)
				{
					for (list<Object*>::iterator Bulletiter = pBulletList->begin(); Bulletiter != pBulletList->end();)
					{
						if (CollisionManager::Collision(*Bulletiter, *Enemyiter))
							Bulletiter = ObjectManager::GetInstance()->ThrowObject(Bulletiter, (*Bulletiter));
						else
							++Bulletiter;
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
	pPlayer->Render();

	ObjectManager::GetInstance()->Render();

	if (Check)
		pUI->Render();

	CursorManager::GetInstance()->WriteBuffer(119.0f, 28.0f, (char*)"\t\t\t\t\t\t\t\t\t\t\t\tCREDIT : ");
	CursorManager::GetInstance()->WriteBuffer(97.0f, 29.0f, (int)(char*)(ObjectManager::GetInstance()->GetCredit()));
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
