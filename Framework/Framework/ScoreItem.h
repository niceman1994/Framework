#pragma once
#include "ItemBridge.h"

class ScoreItem : public ItemBridge
{
public:
	virtual void Initialize()override;
	virtual int Update(Transform& Info)override;
	virtual void Render()override;
	virtual void Release()override;

	virtual Bridge* Clone()override { return new ScoreItem(*this); }
public:
	ScoreItem();
	virtual ~ScoreItem();
};
