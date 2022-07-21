#pragma once
#include "Scene.h"

class StageUI : public Scene
{
public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render()override;
	virtual void Release()override;
public:
	StageUI();
	virtual ~StageUI();
};

