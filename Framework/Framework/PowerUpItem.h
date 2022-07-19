#pragma once
#include "ItemBridge.h"

class PowerUpItem : public ItemBridge
{
public:
	virtual void Initialize()override;
	virtual int Update(Transform& Info)override;
	virtual void Render()override;
	virtual void Release()override;

	virtual Bridge* Clone()override { return new PowerUpItem(*this); }
public:
	PowerUpItem();
	virtual ~PowerUpItem();
};

