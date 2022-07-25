#pragma once
#include "Headers.h"

class Object;
class Bridge
{
protected:
	Object* pObject;
	string BridgeKey;
public:
	virtual void Initialize()PURE;
	virtual int Update(Transform& Info)PURE;
	virtual void Render()PURE;
	virtual void Release()PURE;

	virtual Bridge* Clone()PURE;
public:
	void SetObject(Object* _Object) { pObject = _Object; }
	string GetBridgeKey() const { return BridgeKey; }
public:
	Bridge() : pObject(nullptr), BridgeKey() {}
	virtual ~Bridge() {}
};