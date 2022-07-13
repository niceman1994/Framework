#include "ObjectPool.h"
#include "Object.h"
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
	CursorManager::GetInstance()->WriteBuffer(152.0f, 0.0f, (char*)"DisableList(Bullet) : ");
	CursorManager::GetInstance()->WriteBuffer(174.0f, 0.0f, DisableList["Bullet"].size());

	CursorManager::GetInstance()->WriteBuffer(152.0f, 1.0f, (char*)"EnableList(Bullet) : ");
	CursorManager::GetInstance()->WriteBuffer(173.0f, 1.0f, EnableList["Bullet"].size());

	CursorManager::GetInstance()->WriteBuffer(152.0f, 2.0f, (char*)"DisableList(Enemy) : ");
	CursorManager::GetInstance()->WriteBuffer(173.0f, 2.0f, DisableList["Enemy"].size());

	CursorManager::GetInstance()->WriteBuffer(152.0f, 3.0f, (char*)"EnableList(Enemy) : ");
	CursorManager::GetInstance()->WriteBuffer(172.0f, 3.0f, EnableList["Enemy"].size());

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
