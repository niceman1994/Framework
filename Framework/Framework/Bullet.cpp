#include "Bullet.h"
#include "CursorManager.h"

Bullet::Bullet() : b(0) { }

Bullet::Bullet(Transform _TransInfo) : Object(_TransInfo) {}

Bullet::~Bullet() { }

void Bullet::Initialize()
{
	b = 0;

	strKey = "Bullet";
	Buffer[0] = (char*)"＼";
	Buffer[1] = (char*)"／";

	TransInfo.Position = Vector3(0.0f, 0.0f);
	TransInfo.Rotation = Vector3(0.0f, 0.0f);
	TransInfo.Scale = Vector3(2.0f, 2.0f);

	//TransInfo.Direction = Vector3(0.1f, -0.06f);
}

int Bullet::Update()
{
	Vector3 Target = Vector3(60.0f, 15.0f);

	float Width = Target.x - TransInfo.Position.x;
	float Height = Target.y - TransInfo.Position.y;

	float Distance = sqrt((Width * Width) + (Height * Height));

	TransInfo.Direction = Vector3(Width / Distance, Height / Distance);

	TransInfo.Position += TransInfo.Direction;

	// Target의 좌표 - 나의 좌표 => 나와 타겟 사이의 길이
	// 1보다 작아져야 비율로 바뀌니 관리가 편하다(피타고라스의 정리)

	TransInfo.Position += TransInfo.Direction;

	return 0;
}

void Bullet::Render()
{
	CursorManager::GetInstance()->WriteBuffer(
		TransInfo.Position, (char*)"ABCDEFG");
}

void Bullet::Release()
{
}