#include "ObjectManager.h"
#include "ObjectFactory.h"
#include "Prototype.h"
#include "ObjectPool.h"
#include "Bullet.h"
#include "Bridge.h"

ObjectManager* ObjectManager::Instance = nullptr;

ObjectManager::ObjectManager() : HitCount(0)
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
		pObject = Prototype::GetInstance()->ProtoTypeObject(_Key)->Clone(); // Key ���� ����

	map<string, list<Object*>>::iterator iter = EnableList->find(_Key);

	if (iter == EnableList->end()) // EnableList�� �ƹ��͵� �������� �ʴ� ���
	{
		list<Object*> TempList; // list<Object*> ��ü�� ��� �ӽ� ����(TempList) ����
		TempList.push_back(pObject); // TempList�� push_back���� �ִ´�
		EnableList->insert(make_pair(pObject->GetKey(), TempList));
	}
	else
		iter->second.push_back(pObject); // string�� �̹� ������ ��� list<Object*> �� _Object�� �ִ´�.
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

list<Object*>* ObjectManager::GetObjectList(string _strKey) // ������ ������ ���� �����ͷ� �������.
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
