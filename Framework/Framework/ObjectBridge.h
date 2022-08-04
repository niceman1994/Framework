#pragma once
#include "Headers.h"

class Object;
class ObjectBridge
{
protected:
	Object* pObject;
	string ObjectBridgeKey;
public:
	virtual void Initialize()PURE;
	virtual int Update(Transform& Info)PURE;
	virtual void Render()PURE;
	virtual void Release()PURE;

	virtual ObjectBridge* Clone()PURE;
public:
	void SetObject(Object* _Object) { pObject = _Object; }
	string GetObjectBridgeKey() const { return ObjectBridgeKey; }
public:
	ObjectBridge() : pObject(nullptr), ObjectBridgeKey() {}
	virtual ~ObjectBridge() {}
};