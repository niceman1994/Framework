#pragma once
#include "Headers.h"

class ScoreManager
{
private:
	static ScoreManager* Instance;
public:
	static ScoreManager* GetInstance()
	{
		if (Instance == nullptr)
			Instance = new ScoreManager();

		return Instance;
	}
private:
	int Credit;
	int Score;
public:
	void SetCredit(int _Credit);
	int GetCredit() const { return Credit; }
	void IncreaseCredit();
	void DecreaseCredit();

	void SetScore(int _Score);
	void AddScore(int _Score);
	int GetStageScore() { return Score; }
private:
	ScoreManager();
public:
	~ScoreManager();
};

