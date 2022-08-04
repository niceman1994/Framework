#pragma once
#include "Headers.h"

class Object;
class Bridge;
class ObjectBridge;
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
	int HitCount;
public:
	void AddObject(string _Key);
	void AddObject(string _Key, Bridge* _Bridge, Vector3 _Position);
	list<Object*>* GetObjectList(string _strKey);
	list<Object*>::iterator ThrowObject(list<Object*>::iterator _Where, Object* _Object);

	void ResetHitCount() { HitCount = 0; }
	void AddHitCount(int _Count) { HitCount += _Count; }
	int GetHitCount() const { return HitCount; }

	void Update();
	void Render();
private:
	ObjectManager();
public:
	~ObjectManager();
};

