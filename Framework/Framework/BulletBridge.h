#pragma once
#include "Bridge.h"

class BulletBridge : public Bridge
{
protected:
	// Bullet�� �����͸� ����
	float Speed;
	int Color;
public:
	virtual void Initialize()PURE;
	virtual int Update(Transform& Info)PURE;
	virtual void Render()PURE;
	virtual void Release()PURE;

	virtual Bridge* Clone()PURE;
public:
	BulletBridge() : Speed(0), Color(0) {};
	//BulletBridge(string _BulletBridge) : Bridge(_BulletBridge), Speed(0), Color(0) {};
	virtual ~BulletBridge() {};
};