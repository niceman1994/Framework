#pragma once
#include "BossParts.h"

class BossParts_RightArms : public BossParts
{
public:
	virtual void Initialize()override;
	virtual int Update(Transform& Info)override;
	virtual void Render()override;
	virtual void Release()override;

	virtual Bridge* Clone()override { return new BossParts_RightArms(*this); }
public:
	BossParts_RightArms();
	virtual ~BossParts_RightArms();
};

