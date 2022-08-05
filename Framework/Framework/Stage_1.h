#pragma once
#include "Scene.h"

class Bridge;
class UserInterface;
class Stage_1 : public Scene
{
private:
	Object* pPlayer;
	Object* pFrontShield;

	UserInterface* pUI;
	int Check;
	char* TextureList[8];
public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render()override;
	virtual void Release()override;
public:
	void Enable_UI();

	void CreateItem(Object* _Object, list<Object*>* _ObjectlistA, list<Object*>* _ObjectlistB);
	void GetItem(Object* _ObjectA, Object* _ObjectB, list<Object*>* _ObjectlistA, list<Object*>* _ObjectlistB);

	void PlayerCollision(Object* _Object, list<Object*>* _Objectlist);
	void EnemyBulletCollision(Object* _Object, list<Object*>* _Objectlist);
	void BossCollision(Object* _Object, list<Object*>* _ObjectlistA, list<Object*>* _ObjectlistB);
	void PlayerBossCollision(Object* _Object, list<Object*>* _Objectlist);
public:
	Stage_1();
	virtual ~Stage_1();
};