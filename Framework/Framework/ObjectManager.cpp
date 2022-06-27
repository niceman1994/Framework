#include "ObjectManager.h"
#include "Object.h"

ObjectManager* ObjectManager::Instance = nullptr;

ObjectManager::ObjectManager() {}

ObjectManager::~ObjectManager() {}

void ObjectManager::AddObject(Object* _Object)
{
	// ObjectList
	map<string, list<Object*>>::iterator iter = ObjectList.find(_Object->GetKey());

	if (iter == ObjectList.end()) // ObjectList에 아무것도 존재하지 않는 경우
	{
		list<Object*> TempList; // Player, Enemy 를 담는 임시 변수(TempList) 선언
		TempList.push_back(_Object); // TempList에 push_back으로 넣는다
		ObjectList.insert(make_pair(_Object->GetKey(), TempList));
	}
	else
		iter->second.push_back(_Object); // string이 이미 존재할 경우 list<Object*> 에 _Object를 넣는다.
}

list<Object*>* ObjectManager::GetObjectList(string _strKey) // 데이터 관리를 위해 포인터로 만들었다.
{
	map<string, list<Object*>>::iterator iter = ObjectList.find(_strKey);

	if (iter == ObjectList.end())
		return nullptr;
	else
		return &iter->second;
}

void ObjectManager::Render()
{
	for (map<string, list<Object*>>::iterator iter = ObjectList.begin(); iter != ObjectList.end(); ++iter)
		for (list<Object*>::iterator iter2 = iter->second.begin(); iter2 != iter->second.end(); ++iter2)
			(*iter2)->Render();
}
