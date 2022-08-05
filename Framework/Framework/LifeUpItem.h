#pragma once
#include "ItemBridge.h"

class LifeUpItem : public ItemBridge
{
public:
	virtual void Initialize()override;
	virtual int Update(Transform& Info)override;
	virtual void Render()override;
	virtual void Release()override;

	virtual Bridge* Clone()override { return new LifeUpItem(*this); }
public:
	LifeUpItem();
	virtual ~LifeUpItem();
};
