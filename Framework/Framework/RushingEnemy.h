#pragma once
#include "EnemyBridge.h"

class RushingEnemy : public EnemyBridge
{
public:
	virtual void Initialize()override;
	virtual int Update(Transform& Info)override;
	virtual void Render()override;
	virtual void Release()override;

	virtual Bridge* Clone()override { return new RushingEnemy(*this); }
public:
	RushingEnemy();
	virtual ~RushingEnemy();
};
