#pragma once
#include "Enemy.h"

class RollingEnemy : public Enemy
{
public:
	virtual Object* Initialize(string _Key) override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;

	virtual Object* Clone() override { return new RollingEnemy(*this); }
public:
	RollingEnemy();
	RollingEnemy(Transform _TransInfo);
	virtual ~RollingEnemy();
};

