#pragma once
#include "EnemyBulletBridge.h"

class BossSpecialBullet : public EnemyBulletBridge
{
public:
	virtual void Initialize()override;
	virtual int Update(Transform& Info)override;
	virtual void Render()override;
	virtual void Release()override;

	virtual Bridge* Clone()override { return new BossSpecialBullet(*this); }
public:
	BossSpecialBullet();
	virtual ~BossSpecialBullet();
};

