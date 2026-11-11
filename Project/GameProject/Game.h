#pragma once
#include "Base/Base.h"

class Game :public Base 
{
	int m_cnt;
public:
	Game();
	void Update();

};
enum eDifficulty
{
	eEasy,
	eNormal,
	eHard
};
extern eDifficulty g_difficulty;