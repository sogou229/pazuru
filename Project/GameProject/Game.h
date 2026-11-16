#pragma once
#include "Base/Base.h"

class Game :public Base 
{
	int m_cnt=0;

	CImage m_桃太郎;
	CImage m_イヌ;
	CImage m_キジ;
	CImage m_サル;

	CImage m_img;

	//盤面の配置情報
	static const int ROW = 4;
	static const int COL = 6;

	int m_tsumType[ROW][COL];
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