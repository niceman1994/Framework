#include "ScoreManager.h"

ScoreManager* ScoreManager::Instance = nullptr;

ScoreManager::ScoreManager()
{
	Life = (char*)"¡á¡á¡á¡á";
}

ScoreManager::~ScoreManager() {}

void ScoreManager::SetCredit(int _Credit)
{
	Credit = _Credit;
}

void ScoreManager::IncreaseCredit()
{
	Credit += 1;
}

void ScoreManager::DecreaseCredit()
{
	Credit -= 1;
}

void ScoreManager::SetScore(int _Score)
{
	Score = _Score;
}

void ScoreManager::AddScore(int _Score)
{
	Score += _Score;
}

void ScoreManager::SetLife(char* _Life)
{
	Life = _Life;
}

void ScoreManager::SubtractLife()
{
	++Life;
	++Life;
}
