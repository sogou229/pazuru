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
	static const int ROW = 6;
	static const int COL = 11;

	int m_tsumType[ROW][COL];

	//ドラッグ中か
	bool m_isDragging;

	//選択したツブの種類
	int m_selectType;

	//選択したツブの数
	int m_selectCount;

	//選択済みのツブ
	bool m_isSelected[ROW][COL];

	//最後に選択した位置
	int m_lastX;
	int m_lastY;

public:
	Game();
	void Update();
	void Draw();

	bool GetTsumPosition(CVector2D mouse, int& x, int& y);
};
enum eDifficulty
{
	eEasy,
	eNormal,
	eHard
};
extern eDifficulty g_difficulty;