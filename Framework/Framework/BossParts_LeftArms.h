#pragma once
#include "BossParts.h"

class BossParts_LeftArms : public BossParts
{
public:
	virtual void Initialize()override;
	virtual int Update(Transform& Info)override;
	virtual void Render()override;
	virtual void Release()override;

	virtual Bridge* Clone()override { return new BossParts_LeftArms(*this); }
public:
	BossParts_LeftArms();
	virtual ~BossParts_LeftArms();
};

