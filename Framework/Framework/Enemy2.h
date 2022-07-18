#pragma once
#include "Object.h"

class Enemy2 : public Object
{
public:
	virtual Object* Initialize(string _Key) override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;

	virtual Object* Clone() override { return new Enemy2(*this); }
public:
	Enemy2();
	Enemy2(Transform _TransInfo);
	virtual ~Enemy2();
};

