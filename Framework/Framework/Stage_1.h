#pragma once
#include "Scene.h"

class Bridge;
class Stage_1 : public Scene
{
private:
	Object* pPlayer;
	Object* pFrontShield;
	Object* pBoss;
public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render()override;
	virtual void Release()override;
public:
	void CreateEnemy();

	void CreateItem(Object* _Object, list<Object*>* _ObjectlistA, list<Object*>* _ObjectlistB);

	void PlayerCollision(Object* _Object, list<Object*>* _Objectlist);
	void EnemyBulletCollision(Object* _Object, list<Object*>* _Objectlist);
	void FrontShieldCollision(Object* _Object, list<Object*>* _Objectlist);
	void BossCollision(Object* _Object, list<Object*>* _ObjectlistA, list<Object*>* _ObjectlistB);
	void PlayerBossCollision(Object* _Object, list<Object*>* _Objectlist);
	void BulletToBulletCollision(Object* _Object, list<Object*>* _ObjectlistA, list<Object*>* _ObjectlistB);
public:
	Stage_1();
	virtual ~Stage_1();
};