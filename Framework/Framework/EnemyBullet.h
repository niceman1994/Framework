#pragma once
#include "Object.h"

class EnemyBullet : public Object
{
public:
	virtual Object* Initialize(string _Key) override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;

	virtual Object* Clone() override { return new EnemyBullet(*this); }
public:
	EnemyBullet();
	EnemyBullet(Transform _TransInfo);
	virtual ~EnemyBullet();
};

