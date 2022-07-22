#pragma once
#include "Bridge.h"

class ItemBridge : public Bridge
{
protected:
	char* ItemText[4];
	float Speed;
	int Color;
public:
	virtual void Initialize()PURE;
	virtual int Update(Transform& Info)PURE;
	virtual void Render()PURE;
	virtual void Release()PURE;

	virtual Bridge* Clone()PURE;
public:
	ItemBridge() : ItemText(), Speed(0), Color(0) {};
	virtual ~ItemBridge() {};
};