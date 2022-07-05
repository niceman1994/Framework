#include "ObjectManager.h"
#include "CollisionManager.h"
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
	
	return &iter->second;
}

void ObjectManager::Update()
{	// ObjectManager로 담은 Enemy를 삭제
	for (map<string, list<Object*>>::iterator iter = ObjectList.begin(); iter != ObjectList.end(); ++iter) // map으로 만든 ObjectList에 iter 반복자로 접근
	{
		for (list<Object*>::iterator iter2 = iter->second.begin(); iter2 != iter->second.end();) // map 두번째인 Value에 iter2 반복자를 만들어 iter의 두번째에 접근
		{
			int result = (*iter2)->Update(); // Update() 함수로 Enemy의 위치가 계속 왼쪽으로 이동하기 때문에 0이하가 되는 경우가 생기는데 그때 숫자 1(BUFFER_OVER)을 반환한다.

			if (result == BUFFER_OVER) // 반환된 숫자가 1(BUFFER_OVER)일 경우 실행되는 삭제 조건문
			{
				Object* Temp = *iter2; // iter2를 임시 오브젝트 Temp에 대입

				iter2 = iter->second.erase(iter2); // 반복자 iter2 접근한 1번째 리스트를 삭제하고 iter2에 대입

				delete Temp;
				Temp = nullptr; // 임시 오브젝트 Temp를 삭제 후 초기화
			}
			else
				++iter2; // 아닐경우 iter2 증가
		}
	}
}

void ObjectManager::Render()
{
	for (map<string, list<Object*>>::iterator iter = ObjectList.begin(); iter != ObjectList.end(); ++iter)
	{
		for (list<Object*>::iterator iter2 = iter->second.begin(); iter2 != iter->second.end(); ++iter2)
		{
			(*iter2)->Render();
		}
	}
}
