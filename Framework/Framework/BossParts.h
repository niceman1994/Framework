#pragma once
#include "Bridge.h"

class BossParts : public Bridge
{
protected:
	char* BossPartsText[16];
	float Speed;
	int Color;
public:
	virtual void Initialize()PURE;
	virtual int Update(Transform& Info)PURE;
	virtual void Render()PURE;
	virtual void Release()PURE;

	virtual Bridge* Clone()PURE;
public:
	BossParts() : Speed(0), Color(0), BossPartsText() {};
	virtual ~BossParts() {};
};