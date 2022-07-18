#pragma once
#include "EnemyBulletBridge.h"

class NormalEnemyBullet : public EnemyBulletBridge
{
public:
	virtual void Initialize()override;
	virtual int Update(Transform& Info)override;
	virtual void Render()override;
	virtual void Release()override;

	virtual Bridge* Clone()override { return new NormalEnemyBullet(*this); }
public:
	NormalEnemyBullet();
	virtual ~NormalEnemyBullet();
};
