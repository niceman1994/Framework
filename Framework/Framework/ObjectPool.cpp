#include "ObjectPool.h"
#include "Object.h"
#include "ObjectManager.h"
#include "CursorManager.h"
#include "CollisionManager.h"

ObjectPool* ObjectPool::Instance = nullptr;
map<string, list<Object*>> ObjectPool::EnableList;

ObjectPool::ObjectPool()
{
	
}

ObjectPool::~ObjectPool()
{
}

void ObjectPool::CatchObject(Object* _Object)
{
	map<string, list<Object*>>::iterator Disableiter = DisableList.find(_Object->GetKey());

	if (Disableiter == DisableList.end())
	{
		list<Object*> TempList;
		TempList.push_back(_Object);
		DisableList.insert(make_pair(_Object->GetKey(), TempList));
	}
	else
		Disableiter->second.push_back(_Object);
}

Object* ObjectPool::ThrowObject(string _Key)
{
	map<string, list<Object*>>::iterator Disableiter = DisableList.find(_Key);

	if (Disableiter != DisableList.end() && Disableiter->second.size())
	{
		Object* pObject = Disableiter->second.front();
		Disableiter->second.pop_front();

		pObject->Initialize(_Key);

		return pObject;
	}

	return nullptr;
}

void ObjectPool::Update()
{
	CursorManager::GetInstance()->WriteBuffer(152.0f, 0.0f, (char*)"EnableList(Bullet) : ", 0);
	CursorManager::GetInstance()->WriteBuffer(173.0f, 0.0f, (int)EnableList["Bullet"].size(), 0);

	CursorManager::GetInstance()->WriteBuffer(152.0f, 0.0f, (char*)"DisableList(Enemy) : ", 0);
	CursorManager::GetInstance()->WriteBuffer(173.0f, 0.0f, (int)DisableList["Enemy"].size(), 0);

	CursorManager::GetInstance()->WriteBuffer(152.0f, 0.0f, (char*)"EnableList(Enemy) : ", 0);
	CursorManager::GetInstance()->WriteBuffer(172.0f, 0.0f, (int)EnableList["Enemy"].size(), 0);

	CursorManager::GetInstance()->WriteBuffer(152.0f, 0.0f, (char*)"DisableList(Bullet) : ", 0);
	CursorManager::GetInstance()->WriteBuffer(174.0f, 0.0f, (int)DisableList["Bullet"].size(), 0);
	
	CursorManager::GetInstance()->WriteBuffer(152.0f, 0.0f, (char*)"DisableList(Item) : ", 0);
	CursorManager::GetInstance()->WriteBuffer(172.0f, 0.0f, (int)DisableList["Item"].size(), 0);
	
	CursorManager::GetInstance()->WriteBuffer(152.0f, 0.0f, (char*)"EnableList(Item) : ", 0);
	CursorManager::GetInstance()->WriteBuffer(171.0f, 0.0f, (int)EnableList["Item"].size(), 0);

	CursorManager::GetInstance()->WriteBuffer(152.0f, 0.0f, (char*)"DisableList(Boss) : ", 0);
	CursorManager::GetInstance()->WriteBuffer(172.0f, 0.0f, (int)DisableList["Boss"].size(), 0);

	CursorManager::GetInstance()->WriteBuffer(152.0f, 0.0f, (char*)"EnableList(Boss) : ", 0);
	CursorManager::GetInstance()->WriteBuffer(171.0f, 0.0f, (int)EnableList["Boss"].size(), 0);

	for (map<string, list<Object*>>::iterator iter = EnableList.begin(); iter != EnableList.end(); ++iter)
	{
		for (list<Object*>::iterator iter2 = iter->second.begin(); iter2 != iter->second.end();)
		{
			int result = (*iter2)->Update();

			switch (result)
			{
				case BUFFER_OVER:
				{
					map<string, list<Object*>>::iterator Disableiter = DisableList.find((*iter2)->GetKey());

					if (Disableiter == DisableList.end())
					{
						list<Object*> TempList;
						TempList.push_back((*iter2));
						DisableList.insert(make_pair((*iter2)->GetKey(), TempList));
					}
					else
						Disableiter->second.push_back((*iter2));

					iter2 = (*iter).second.erase(iter2);
				}

				case 2:
				{
					CursorManager::GetInstance()->WriteBuffer(50.0f, 1.0f, (char*)"충돌입니다.");
					++iter2;
				}
					break;

				default:
					++iter2;
			}
		}
	}
}
