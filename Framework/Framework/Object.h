#pragma once
#include "Headers.h"
#include "Bridge.h"

// Object.h에 bool 변수를 

class Object
{
protected:
	Transform TransInfo;
	string strKey;
	char* Buffer[64];
	int HitCount;

	Bridge* pBridge;
public:
	virtual Object* Initialize(string _Key)PURE;
	virtual int Update()PURE;
	virtual void Render()PURE;
	virtual void Release()PURE;

	virtual Object* Clone()PURE;
public:
	string GetKey() const { return strKey; }

  	Vector3 GetPosition() const { return TransInfo.Position; }
	void SetPosition(float _x, float _y) { TransInfo.Position = Vector3(_x, _y); }
	void SetPosition(Vector3 _Position) { TransInfo.Position = _Position; }

	Vector3 GetScale() const { return TransInfo.Scale; }
	void SetScale(float _x, float _y) { TransInfo.Scale = Vector3(_x, _y); }

	void SetBridge(Bridge* _Bridge) { pBridge = _Bridge; }

	string GetBridgeName() const
	{
		if (pBridge != nullptr)
			return pBridge->GetBridgeKey();
		else
			return "";
	}

	void AddBossHitCount() { ++HitCount; }
	int BossHitCount() const { return HitCount; }
	void ResetBossHitCount() { HitCount = 0; }
public:
	Object();
	Object(Transform _TransInfo);
	virtual ~Object();
};

