#include "BackGround.h"

BackGround::BackGround() {}
BackGround::BackGround(Transform _TransInfo) : Object(_TransInfo) {}
BackGround::~BackGround() {}

Object* BackGround::Initialize(string _Key)
{
    strKey = "BackGround";

    return this;
}

int BackGround::Update()
{
    return 0;
}

void BackGround::Render()
{
}

void BackGround::Release()
{
}
