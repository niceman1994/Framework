#include "ObjectManager.h"
#include "ObjectPool.h"
#include "Object.h"

ObjectManager* ObjectManager::Instance = nullptr;

ObjectManager::ObjectManager() 
{
	EnableList = ObjectPool::GetEnableList();
	DisableList = ObjectPool::GetInstance()->GetDisableList();
}

ObjectManager::~ObjectManager() {}

void ObjectManager::AddObject(Object* _Object)
{
	// ObjectList
	map<string, list<Object*>>::iterator iter = EnableList->find(_Object->GetKey());

	if (iter == EnableList->end()) // ObjectList에 아무것도 존재하지 않는 경우
	{
		list<Object*> TempList; // Player, Enemy 를 담는 임시 변수(TempList) 선언
		TempList.push_back(_Object); // TempList에 push_back으로 넣는다
		EnableList->insert(make_pair(_Object->GetKey(), TempList));
	}
	else
		iter->second.push_back(_Object); // string이 이미 존재할 경우 list<Object*> 에 _Object를 넣는다.
}

list<Object*>* ObjectManager::GetObjectList(string _strKey) // 데이터 관리를 위해 포인터로 만들었다.
{
	map<string, list<Object*>>::iterator iter = EnableList->find(_strKey);

	if (iter == EnableList->end())
		return nullptr;

	return &iter->second;
}

list<Object*>::iterator ObjectManager::ThrowObject(list<Object*>::iterator _Where, Object* _Object)
{
	map<string, list<Object*>>::iterator iter = EnableList->find(_Object->GetKey());
	
	if (iter == EnableList->end())
		return _Where;

	ObjectPool::GetInstance()->CatchObject(_Object);

	return iter->second.erase(_Where);
}

list<Object*>* ObjectManager::GetDisObjectList(string _strKey)
{
	map<string, list<Object*>>::iterator Disiter = DisableList->find(_strKey);
	map<string, list<Object*>>::iterator Eniter = EnableList->find(_strKey);

	if (Disiter->second.size() >= 20)
	{
		Disiter->second = Eniter->second;

		return &Disiter->second;
	}
}

void ObjectManager::Update()
{	
	ObjectPool::GetInstance()->Update();
}

void ObjectManager::Render()
{
	for (map<string, list<Object*>>::iterator iter = EnableList->begin(); iter != EnableList->end(); ++iter)
	{
		for (list<Object*>::iterator iter2 = iter->second.begin(); iter2 != iter->second.end(); ++iter2)
		{
			(*iter2)->Render();
		}
	}
}
