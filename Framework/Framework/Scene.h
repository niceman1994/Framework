#pragma once
#include "Headers.h"

class Scene
{
protected:
	string str;
public:
	virtual void Initialize()PURE; // PURE는 순수 가상 함수를 의미하는 = 0 을 의미한다.
	virtual void Update()PURE;
	virtual void Render()PURE;
	virtual void Release()PURE;
public:
	Scene();
	Scene(string _str);
	~Scene();
};