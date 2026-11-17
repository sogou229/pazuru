#include"Game.h"
#include"Title.h"
#include"Enemy.h"
#include"Player.h"
#include"HpBar.h"
#include<cstdlib>
#include<ctime>
//#include"GameClear.h"
//#include"GameOver.h"


eDifficulty g_difficulty = eNormal;

Game::Game() :Base(eType_Scene)
{
	//盤面画像
	m_img.Load("Image/盤面.png");

	m_img.SetSize(1000, 1160);
	m_img.SetCenter(500, 600);
	m_img.SetPos(CVector2D(960, 540));

	//ツブ画像
	m_桃太郎.Load("Image/仮桃太郎.png");
	m_イヌ.Load("Image/仮イヌ.png");
	m_キジ.Load("Image/仮キジ.png");
	m_サル.Load("image/仮サル.png");
	
	//ランダム用の初期化
	static bool seeded = false;

	if (!seeded)
	{
		srand((unsigned int)time(nullptr));
		seeded = true;
	}
	// ツムの種類をランダム決定
	for (int y = 0; y < ROW; y++)
	{
		for (int x = 0; x < COL; x++)
		{
			m_tsumType[y][x] = rand() % 4;
		}
	}
	for (int y = 0; y < ROW; y++) 
	{
		for (int x = 0; x < COL; x++)
		{
			m_isSelected[y][x] = false;
		}
	}
	new HpBar(false, 100);
	new HpBar(true, 100);

	new Enemy(CVector2D(960, 540));
}
void Game::Update()
{
	CVector2D mouse = CInput::GetMousePoint();

	int x, y;

	// マウスを押した瞬間
	if (PUSH(CInput::eMouseL))
	{
		if (GetTsumPosition(mouse, x, y))
		{
			m_isDragging = true;

			m_selectType = m_tsumType[y][x];

			m_isSelected[y][x] = true;

			m_selectCount = 1;

			m_lastX = x;
			m_lastY = y;
		}
	}

	// ドラッグ中
	if (HOLD(CInput::eMouseL) && m_isDragging)
	{
		if (GetTsumPosition(mouse, x, y))
		{
			int dx = abs(x - m_lastX);
			int dy = abs(y - m_lastY);

			if (!m_isSelected[y][x])
			{
				// 隣接しているか確認
				if (dx <= 1 && dy <= 1 &&
					(dx + dy > 0))
				{
					// 同じ種類か確認
					if (m_tsumType[y][x] == m_selectType)
					{
						m_isSelected[y][x] = true;

						m_selectCount++;

						m_lastX = x;
						m_lastY = y;
					}
				}
			}
		}
	}

	// マウスを離した瞬間
	if (PULL(CInput::eMouseL))
	{
		m_isDragging = false;

		for (int j = 0; j < ROW; j++)
		{
			for (int i = 0; i < COL; i++)
			{
				m_isSelected[j][i] = false;
			}
		}

		m_selectCount = 0;
	}

}
void Game::Draw()
{
	m_img.Draw();

	//ツブの大きさ
	float size = 60.0f;

	//配置開始画面
	float startX = 610.0f;
	float startY = 660.0f;

	//ツブの間隔
	float gapX = 70.0f;
	float gapY = 78.0f;

	for (int y = 0; y < ROW; y++)
	{
		for (int x = 0; x < COL; x++)
		{
			CVector2D pos(
				startX + x * gapX,
				startY + y * gapY
			);

			switch (m_tsumType[y][x])
			{
			case 0:
				m_桃太郎.SetSize(size, size);
				m_桃太郎.SetCenter(size / 2, size / 2);
				m_桃太郎.SetPos(pos);
				m_桃太郎.Draw();
				break;

			case 1:
				m_イヌ.SetSize(size, size);
				m_イヌ.SetCenter(size / 2, size / 2);
				m_イヌ.SetPos(pos);
				m_イヌ.Draw();
				break;

			case 2:
				m_キジ.SetSize(size, size);
				m_キジ.SetCenter(size / 2, size / 2);
				m_キジ.SetPos(pos);
				m_キジ.Draw();
				break;

			case 3:
				m_サル.SetSize(size, size);
				m_サル.SetCenter(size / 2, size / 2);
				m_サル.SetPos(pos);
				m_サル.Draw();
				break;
			}
		}
	}
}
bool Game::GetTsumPosition(CVector2D mouse, int& x, int& y)
{

	float size = 110.0f;

	float startX = 344.0f;
	float startY = 606.0f;

	float gapX = 248.0f;
	float gapY = 134.0f;

	for (int j = 0; j < ROW; j++)
	{
		for (int i = 0; i < COL; i++)
		{
			float cx = startX + i * gapX;
			float cy = startY + j * gapY;

			if (mouse.x >= cx - size / 2 &&
				mouse.x <= cx + size / 2 &&
				mouse.y >= cy - size / 2 &&
				mouse.y <= cy + size / 2)
			{
				x = i;
				y = j;
				return true;
			}
		}
	}

	return false;
}