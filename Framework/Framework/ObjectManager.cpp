#include "ObjectManager.h"
#include "ObjectFactory.h"
#include "Prototype.h"
#include "ObjectPool.h"
#include "Bullet.h"
#include "Bridge.h"

ObjectManager* ObjectManager::Instance = nullptr;

ObjectManager::ObjectManager() : Credit(0), Score(0)
{
	EnableList = ObjectPool::GetEnableList();
}

ObjectManager::~ObjectManager() 
{

}

void ObjectManager::AddObject(string _Key)
{
	// ObjectList
	Object* pObject = ObjectPool::GetInstance()->ThrowObject(_Key);

	if (pObject == nullptr)
		pObject = Prototype::GetInstance()->ProtoTypeObject(_Key)->Clone(); // Key 값을 전달

	map<string, list<Object*>>::iterator iter = EnableList->find(_Key);

	if (iter == EnableList->end()) // EnableList에 아무것도 존재하지 않는 경우
	{
		list<Object*> TempList; // list<Object*> 객체를 담는 임시 변수(TempList) 선언
		TempList.push_back(pObject); // TempList에 push_back으로 넣는다
		EnableList->insert(make_pair(pObject->GetKey(), TempList));
	}
	else
		iter->second.push_back(pObject); // string이 이미 존재할 경우 list<Object*> 에 _Object를 넣는다.
}

void ObjectManager::AddObject(string _Key, Bridge* _Bridge, Vector3 _Position)
{
	Object* pObject = ObjectPool::GetInstance()->ThrowObject(_Key);

	if (pObject == nullptr)
		pObject = Prototype::GetInstance()->ProtoTypeObject(_Key)->Clone();

	_Bridge->Initialize();
	_Bridge->SetObject(pObject);

	pObject->SetBridge(_Bridge);
	pObject->SetPosition(_Position);

	map<string, list<Object*>>::iterator iter = EnableList->find(_Key);

	if (iter == EnableList->end())
	{
		list<Object*> TempList;
		TempList.push_back(pObject);
		EnableList->insert(make_pair(pObject->GetKey(), TempList));
	}
	else
		iter->second.push_back(pObject);
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
