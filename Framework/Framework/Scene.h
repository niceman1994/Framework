#pragma once
#include "Headers.h"
#include "Object.h"

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
	void BulletPassBy(list<Object*>* _Objectlist);
	void EnemyBulletPassBy(list<Object*>* _Objectlist);
	void ObjectPassBy(list<Object*>* _Object, list<Object*>* _Objectlist);

	void PlayerLifeState();
public:
	Scene();
	virtual ~Scene();
};