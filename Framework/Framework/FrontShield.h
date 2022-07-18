#pragma once
#include "Object.h"

class FrontShield : public Object
{
public:
	virtual Object* Initialize(string _Key) override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;

	virtual Object* Clone() override { return new FrontShield(*this); }
public:
	FrontShield();
	FrontShield(Transform _TransInfo);
	virtual ~FrontShield();
};
