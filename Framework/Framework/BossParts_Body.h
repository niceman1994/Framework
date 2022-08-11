#pragma once
#include "BossParts.h"
#include "Boss.h"

class BossParts_Body : public BossParts
{
private:
	Object* Boss_Left = new Boss;
	Object* Boss_Right = new Boss;
public:
	virtual void Initialize()override;
	virtual int Update(Transform& Info)override;
	virtual void Render()override;
	virtual void Release()override;

	virtual Bridge* Clone()override { return new BossParts_Body(*this); }
public:
	BossParts_Body();
	virtual ~BossParts_Body();
};
