#include "BackGround.h"
#include "CursorManager.h"

BackGround::BackGround() : TextureList() {}
BackGround::BackGround(Transform _TransInfo) : Object(_TransInfo), TextureList() {}
BackGround::~BackGround() {}

Object* BackGround::Initialize(string _Key)
{
    strKey = _Key;

    TextureList[0] = (char*)
        "£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß£ß";

    TextureList[1] = (char*)
        "£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ£þ";
    TransInfo.Position = Vector3(0.0f,0.0f);
    TransInfo.Rotation = Vector3(0.0f, 0.0f);
    TransInfo.Scale = Vector3(180.0f, 6.0f);

    return this;
}

int BackGround::Update()
{
    //TransInfo.Position.x -= 1.0f;

    return 0;
}

void BackGround::Render()
{
    CursorManager::GetInstance()->WriteBuffer(0.0f, 1.0f, TextureList[0]);
    CursorManager::GetInstance()->WriteBuffer(0.0f, 48.0f, TextureList[1]);
}

void BackGround::Release()
{
}
