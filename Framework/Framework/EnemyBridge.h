#pragma once
#include "Bridge.h"

class EnemyBridge : public Bridge
{
protected:
	char* ObjectText[8];
	float Speed;
	int Color;
public:
	virtual void Initialize()PURE;
	virtual int Update(Transform& Info)PURE;
	virtual void Render()PURE;
	virtual void Release()PURE;

	virtual Bridge* Clone()PURE;
public:
	EnemyBridge() : Speed(0), Color(0), ObjectText() {};
	virtual ~EnemyBridge() {};
};