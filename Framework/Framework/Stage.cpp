#include "Stage.h"
#include "Player.h"
#include "SceneManager.h"
#include "ObjectManager.h"

Stage::Stage() : pPlayer(nullptr) {}

Stage::~Stage() { Release(); }

void Stage::Initialize()
{
	// 1. 반환형태가 Object* 이거나 && list<Object*>
	// 2. Key 가 전달되어야 함.
	list<Object*>* pPlayerList = ObjectManager::GetInstance()->GetObjectList("Player");

	if(pPlayerList != nullptr)
		pPlayer = pPlayerList->front()->Clone();
}

void Stage::Update()
{
	if (pPlayer)
		pPlayer->Update();
}

void Stage::Render()
{
	if (pPlayer)
		pPlayer->Render();

	ObjectManager::GetInstance()->Render();
}

void Stage::Release()
{
	::Safe_Delete(pPlayer);
}