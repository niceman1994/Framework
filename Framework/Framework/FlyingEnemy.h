#pragma once
#include "Enemy.h"

class FlyingEnemy : public Enemy
{
public:
	virtual Object* Initialize(string _Key) override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;

	virtual Object* Clone() override { return new FlyingEnemy(*this); }
public:
	FlyingEnemy();
	FlyingEnemy(Transform _TransInfo);
	virtual ~FlyingEnemy();
};

