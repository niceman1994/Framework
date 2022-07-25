#pragma once
#include "ItemBridge.h"

class LifeItem : public ItemBridge
{
public:
	virtual void Initialize()override;
	virtual int Update(Transform& Info)override;
	virtual void Render()override;
	virtual void Release()override;

	virtual Bridge* Clone()override { return new LifeItem(*this); }
public:
	LifeItem();
	virtual ~LifeItem();
};

