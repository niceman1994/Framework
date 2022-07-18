#pragma once
#include "Headers.h"

class Object;
class ItemBridge
{
protected:
	Object* pObject;
public:
	virtual void Initialize()PURE;
	virtual int Update(Transform& Info)PURE;
	virtual void Render()PURE;
	virtual void Release()PURE;

	virtual ItemBridge* Clone()PURE;
public:
	void SetObject(Object* _Object) { pObject = _Object; }
public:
	ItemBridge() : pObject(nullptr) {}
	virtual ~ItemBridge() {}
};