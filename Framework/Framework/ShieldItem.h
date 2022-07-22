#pragma once
#include "ItemBridge.h"

class ShieldItem : public ItemBridge
{
public:
	virtual void Initialize()override;
	virtual int Update(Transform& Info)override;
	virtual void Render()override;
	virtual void Release()override;

	virtual Bridge* Clone()override { return new ShieldItem(*this); }
public:
	ShieldItem();
	virtual ~ShieldItem();
};

