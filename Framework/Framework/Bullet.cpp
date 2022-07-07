#include "Bullet.h"
#include "CursorManager.h"
#include "MathManager.h"

Bullet::Bullet() { }
Bullet::Bullet(Transform _TransInfo) : Object(_TransInfo) { }
Bullet::~Bullet() { }


void Bullet::Initialize()
{
	strKey = "Bullet";

	Buffer[0] = (char*)"＼";
	Buffer[1] = (char*)"／";

	TransInfo.Position = Vector3(0.0f, 0.0f);
	TransInfo.Rotation = Vector3(0.0f, 0.0f);
	TransInfo.Scale = Vector3(float(strlen(Buffer[0])), (float)MAX_SIZE);

	TransInfo.Direction = Vector3(0.0f, 0.0f);

	Color = 12;
}

int Bullet::Update()
{
	//printf_s("%f\n", TransInfo.Direction.x);
	//printf_s("%f\n", TransInfo.Direction.y);

	// Target의 좌표 - 나의 좌표 => 나와 타겟 사이의 길이
	// 1보다 작아져야 비율로 바뀌니 관리가 편하다(피타고라스의 정리)

	TransInfo.Direction = MathManager::GetDirection(
		TransInfo.Position, Vector3(60.0f, 15.0f));

	TransInfo.Position += TransInfo.Direction;

	float Distance = MathManager::GetDistance(
		TransInfo.Position, Vector3(60.0f, 15.0f));

	if (Distance < 4)
		return 2;

	return 0;
}

void Bullet::Render()
{
	for (int i = 0; i < MAX_SIZE; ++i)
	{
		CursorManager::GetInstance()->WriteBuffer(
			TransInfo.Position.x,
			TransInfo.Position.y + i,
			Buffer[i], Color);
	}
}

void Bullet::Release()
{

}

