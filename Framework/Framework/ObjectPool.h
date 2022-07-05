#pragma once
#include "Headers.h"

class Object; // 클래스 전방선언, 선언만 하고 존재하지는 않아서 포인터로 다뤄야 한다.
class ObjectPool
{
private:
	static ObjectPool* Instance;
public:
	static ObjectPool* GetInstance()
	{
		if (Instance == nullptr)
			Instance = new ObjectPool();

		return Instance;
	}
private:
	map<string, list<Object*>> EnableList;
	map<string, list<Object*>> DisableList;
public:
	void AddObject(string _Key, list<Object*> _List);
	void AddObject(Object* _Object);
	void Update();
private:
	ObjectPool();
public:
	~ObjectPool();
};

