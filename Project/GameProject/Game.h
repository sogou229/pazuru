#pragma once
#include "Base/Base.h"

class Game :public Base 
{
	int m_cnt=0;

	CImage m_img;
public:
	Game();
	void Update();
	void Draw();

};
enum eDifficulty
{
	eEasy,
	eNormal,
	eHard
};
extern eDifficulty g_difficulty;