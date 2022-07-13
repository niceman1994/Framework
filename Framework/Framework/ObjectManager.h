#pragma once
#include "Headers.h"

class Object;
class Bridge;
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
	int Score;
	int PlayerHp;
public:
	void AddObject(string _Key);
	void AddObject(string _Key, Bridge* _Bridge, Vector3 _Position);
	list<Object*>* GetObjectList(string _strKey);
	list<Object*>::iterator ThrowObject(list<Object*>::iterator _Where, Object* _Object);

	void SetCredit(int _Credit) { Credit = _Credit; }
	int GetCredit() const { return Credit; }
	void IncreaseCredit() { Credit += 1; }
	void DecreaseCredit() { Credit -= 1; }

	void SetScore(int _Score) { Score = _Score; }
	void GetStageScore(int _Score) { Score += _Score; }
	int FinalScore() const { return Score; }

	void SetHp(int _hp) { PlayerHp = _hp; }
	void SubHp(int _hp) { PlayerHp -= _hp; }
	int GetHp() const { return PlayerHp; }

	void Update();
	void Render();
private:
	ObjectManager();
public:
	~ObjectManager();
};

