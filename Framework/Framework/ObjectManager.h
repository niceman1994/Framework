#pragma once
#include "Headers.h"

class Object;
class ObjectManager
{
private:
	static ObjectManager* Instance;
public:
	static ObjectManager* GetInstance()
	{
		if (Instance == nullptr)
			Instance = new ObjectManager();

		return Instance;
	}
private:
	map<string, list<Object*>>* EnableList;
	int Credit;
public:
	void AddObject(string _Key);
	void AddObject(Object* _Object);
	list<Object*>* GetObjectList(string _strKey);
	list<Object*>::iterator ThrowObject(list<Object*>::iterator _Where, Object* _Object);
	void SetCredit(int _Credit) { Credit = _Credit; }
	int GetCredit() const { return Credit; }
	void IncreaseCredit() { Credit += 1; }
	void DecreaseCredit() { Credit -= 1; }
	void Update();
	void Render();
private:
	ObjectManager();
public:
	~ObjectManager();
};

