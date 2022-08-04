#pragma once
#include "EnemyBridge.h"

class FlyingEnemy : public EnemyBridge
{
public:
	virtual void Initialize()override;
	virtual int Update(Transform& Info)override;
	virtual void Render()override;
	virtual void Release()override;

	virtual Bridge* Clone()override { return new FlyingEnemy(*this); }
public:
	FlyingEnemy();
	virtual ~FlyingEnemy();
};
