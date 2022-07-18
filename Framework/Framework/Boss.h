#pragma once
#include "Object.h"

class Boss : public Object
{
public:
	virtual Object* Initialize(string _Key) override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;

	virtual Object* Clone() override { return new Boss(*this); }
public:
	Boss();
	Boss(Transform _TransInfo);
	virtual ~Boss();
};

