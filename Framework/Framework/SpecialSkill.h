#pragma once
#include "BulletBridge.h"

class SpecialSkill : public BulletBridge
{
public:
	virtual void Initialize()override;
	virtual int Update(Transform& Info)override;
	virtual void Render()override;
	virtual void Release()override;

	virtual Bridge* Clone()override { return new SpecialSkill(*this); }
public:
	SpecialSkill();
	virtual ~SpecialSkill();
};

