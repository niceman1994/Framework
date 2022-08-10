#include "Scene.h"
#include "ObjectManager.h"
#include "ScoreManager.h"
#include "CursorManager.h"

Scene::Scene() : Text(), count(0) { }
Scene::~Scene() { }

void Scene::BulletPassBy(list<Object*>* _Objectlist)
{
	if (_Objectlist != nullptr)
	{
		for (list<Object*>::iterator Bulletiter = _Objectlist->begin(); Bulletiter != _Objectlist->end(); )
		{
			if ((*Bulletiter)->GetPosition().x >= 178.0f)
				Bulletiter = ObjectManager::GetInstance()->ThrowObject(Bulletiter, (*Bulletiter));
			else
				++Bulletiter;
		}
	}
}

void Scene::EnemyBulletPassBy(list<Object*>* _Objectlist)
{
	if (_Objectlist != nullptr)
	{
		for (list<Object*>::iterator iter = _Objectlist->begin(); iter != _Objectlist->end();)
		{
			if ((*iter)->GetPosition().x <= 0.0f)
				iter = ObjectManager::GetInstance()->ThrowObject(iter, (*iter));
			else
				++iter;
		}
	}
}

void Scene::ObjectPassBy(list<Object*>* _Object, list<Object*>* _Objectlist)
{
	if (_Object != nullptr)
	{
		for (list<Object*>::iterator Enemyiter = _Object->begin(); Enemyiter != _Object->end();)
		{
			if (_Objectlist != nullptr)
			{
				for (list<Object*>::iterator iter = _Objectlist->begin(); iter != _Objectlist->end();)
				{
					if ((*iter)->GetPosition().x <= 0.0f)
						iter = ObjectManager::GetInstance()->ThrowObject(iter, (*iter));
					else
						++iter;
				}
			}

			if ((*Enemyiter)->GetPosition().x <= 0.0f)
				Enemyiter = ObjectManager::GetInstance()->ThrowObject(Enemyiter, *Enemyiter);
			else
				++Enemyiter;
		}
	}
}

void Scene::PlayerLifeState()
{
	if (ObjectManager::GetInstance()->GetPlayerHitCount() == 0)
		ObjectManager::GetInstance()->SetLife((char*)"¡á¡á¡á¡á");

	else if (ObjectManager::GetInstance()->GetPlayerHitCount() == 1)
 		ObjectManager::GetInstance()->SetLife((char*)"¡á¡á¡á");

	else if (ObjectManager::GetInstance()->GetPlayerHitCount() == 2)
		ObjectManager::GetInstance()->SetLife((char*)"¡á¡á");

	else if (ObjectManager::GetInstance()->GetPlayerHitCount() == 3)
		ObjectManager::GetInstance()->SetLife((char*)"¡á");

	else if (ObjectManager::GetInstance()->GetPlayerHitCount() == 4)
	{
		Object* pPlayer = ObjectManager::GetInstance()->GetObjectList("Player")->front();

		ObjectManager::GetInstance()->SetLife((char*)"¡á¡á¡á¡á");
		pPlayer->Initialize("Player");
		ObjectManager::GetInstance()->ResetPlayerHitCount();
	}
}
