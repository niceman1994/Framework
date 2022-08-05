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
	int PlayerHitCount;
	char* Life;
public:
	void AddObject(string _Key);
	void AddObject(string _Key, Bridge* _Bridge, Vector3 _Position);
	list<Object*>* GetObjectList(string _strKey);
	list<Object*>::iterator ThrowObject(list<Object*>::iterator _Where, Object* _Object);

	void ResetHitCount() { HitCount = 0; }
	void AddHitCount(int _Count) { HitCount += _Count; }
	int GetHitCount() const { return HitCount; }

	void ResetPlayerHitCount() { PlayerHitCount = 0; }
	void AddPlayerHitCount(int _Count) { PlayerHitCount += _Count; }
	void SubtractPlayerHitCount(int _Count) 
	{ 
		if(PlayerHitCount >=1 && PlayerHitCount <=3)
			PlayerHitCount -= _Count; 
	}
	int GetPlayerHitCount() const { return PlayerHitCount; }

	void SetLife(char* _Life) { Life = _Life; }
	char* LifeState() const { return Life; }

	void Update();
	void Render();
private:
	ObjectManager();
public:
	~ObjectManager();
};

