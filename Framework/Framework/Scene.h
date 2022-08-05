#pragma once
#include "Headers.h"
#include "Object.h"

class Scene
{
protected:
	int count;
	char* Text[36];
public:
	virtual void Initialize()PURE; // PURE는 순수 가상 함수를 의미하는 = 0 을 의미한다.
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