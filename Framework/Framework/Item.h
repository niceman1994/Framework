#pragma once
#include "Object.h"

class Item : public Object
{
public:
	virtual Object* Initialize(string _Key) override;
	virtual int Update() override;
	virtual void Render() override;
	virtual void Release() override;

	virtual Object* Clone() override { return new Item(*this); }
public:
	Item();
	Item(Transform _TransInfo);
	virtual ~Item();
};
