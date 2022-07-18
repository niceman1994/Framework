#pragma once
#include "Bridge.h"

class EnemyBulletBridge : public Bridge
{
protected:
	float Speed;
	int Color;
public:
	virtual void Initialize()PURE;
	virtual int Update(Transform& Info)PURE;
	virtual void Render()PURE;
	virtual void Release()PURE;

	virtual Bridge* Clone()PURE;
public:
	EnemyBulletBridge() : Speed(0), Color(0) {};
	virtual ~EnemyBulletBridge() {};
};