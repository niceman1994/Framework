#pragma once
#include "BulletBridge.h"

class TwinBullet : public BulletBridge
{
public:
	virtual void Initialize()override;
	virtual int Update(Transform& Info)override;
	virtual void Render()override;
	virtual void Release()override;
public:
	TwinBullet();
	virtual ~TwinBullet();
};

