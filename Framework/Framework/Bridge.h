#pragma once
#include "Headers.h"

class Object;
class Bridge
{
protected:
	Object* pObject;
	string BridgeKey;
	//int BossHit;
public:
	virtual void Initialize()PURE;
	virtual int Update(Transform& Info)PURE;
	virtual void Render()PURE;
	virtual void Release()PURE;

	virtual Bridge* Clone()PURE;
public:
	void SetObject(Object* _Object) { pObject = _Object; }
	string GetBridgeKey() const { return BridgeKey; }

	//void AddBossHitCount() { ++BossHit; }
	//int GetBossHitCount() const { return BossHit; }
	//void ResetBossHitCount() { BossHit = 0; }
public:
	Bridge() : pObject(nullptr), BridgeKey() {}
	virtual ~Bridge() {}
};