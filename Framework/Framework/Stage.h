#pragma once
#include "Scene.h"

class Object;
class UserInterface;
class Stage : public Scene
{
private:
	UserInterface* pUI;
	int Check;
	int Score;
public:
	virtual void Initialize()override;
	virtual void Update()override;
	virtual void Render()override;
	virtual void Release()override;
public:
	void Enable_UI();

	void SetScore(int _Score) { Score = _Score; }
	int GetScore() const { return Score; }
public:
	Stage();
	virtual ~Stage();
};