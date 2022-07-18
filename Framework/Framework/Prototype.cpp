#include "Prototype.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Enemy2.h"
#include "Boss.h"
#include "EnemyBullet.h"

Prototype* Prototype::Instance = nullptr;

Prototype::Prototype()
{
}

Prototype::~Prototype()
{
}

void Prototype::Initialize()
{
	Transform Info;

	string Key = "Player";
	ProtoTypeList[Key] = (new Player(Info))->Initialize(Key); // new Player로 할당하고 Initialize(Key)로 초기값 지정 후 ProtoTypeList[Key]로 반환

	Key = "Enemy";
	ProtoTypeList[Key] = (new Enemy(Info))->Initialize(Key);

	Key = "Enemy2";
	ProtoTypeList[Key] = (new Enemy2(Info))->Initialize(Key);

	Key = "Boss";
	ProtoTypeList[Key] = (new Boss(Info))->Initialize(Key);

	Key = "Bullet";
	ProtoTypeList[Key] = (new Bullet(Info))->Initialize(Key);

	Key = "EnemyBullet";
	ProtoTypeList[Key] = (new EnemyBullet(Info))->Initialize(Key);
}

Object* Prototype::ProtoTypeObject(string _Key)
{
	map<string, Object*>::iterator iter = ProtoTypeList.find(_Key);

	if (iter == ProtoTypeList.end())
		return nullptr;

	return iter->second;
}
