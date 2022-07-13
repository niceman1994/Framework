#include "BackGround.h"

BackGround::BackGround() {}
BackGround::BackGround(Transform _TransInfo) : Object(_TransInfo) {}
BackGround::~BackGround() {}

Object* BackGround::Initialize(string _Key)
{
    strKey = "BackGround";

    TextureList.push_back("");

    TransInfo.Position = Vector3(0.0f, 50.0f);
    TransInfo.Rotation = Vector3(0.0f, 0.0f);
    TransInfo.Scale = Vector3(5.0f, 5.0f);

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
