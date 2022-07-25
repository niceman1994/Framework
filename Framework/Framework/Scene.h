#pragma once
#include "Headers.h"
class Object;
class Scene
{
protected:
	int count;
	char* Text[36];
public:
	virtual void Initialize()PURE; // PURE�� ���� ���� �Լ��� �ǹ��ϴ� = 0 �� �ǹ��Ѵ�.
	virtual void Update()PURE;
	virtual void Render()PURE;
	virtual void Release()PURE;

protected:
	
	void Collsion(list<Object*>* Bullet);
public:
	Scene();
	virtual ~Scene();
};