#include "Scene.h"
#include "ObjectManager.h"

void Scene::Collsion(list<Object*>* Bullet)
{
	if (Bullet != nullptr)
	{
		for (list<Object*>::iterator Bulletiter = Bullet->begin(); Bulletiter != Bullet->end(); )
		{
			if ((*Bulletiter)->GetPosition().x >= 178.0f)
				Bulletiter = ObjectManager::GetInstance()->ThrowObject(Bulletiter, (*Bulletiter));
			else
				++Bulletiter;
		}
	}
}

Scene::Scene() : Text(), count(0) { }
Scene::~Scene() { }
