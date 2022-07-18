#include "Boss.h"
#include "CursorManager.h"
#include "ObjectManager.h"

Boss::Boss() {}

Boss::Boss(Transform _TransInfo) : Object(_TransInfo) {}

Boss::~Boss() {}

Object* Boss::Initialize(string _Key)
{
	strKey = _Key;

	

	return this;
}

int Boss::Update()
{
	return 0;
}

void Boss::Render()
{
}

void Boss::Release()
{
}
