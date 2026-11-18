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
			//ツムの種類
			m_tsumType[y][x] = rand() % 4;

			//最初は１個分の大きさ
			m_tsumCount[y][x] = 1;

			m_tsumOffsetY[y][x] - 0.0f;
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
	// 落下アニメーション
	if (m_isFalling)
	{
		bool stillFalling = false;

		for (int y = 0; y < ROW; y++)
		{
			for (int x = 0; x < COL; x++)
			{
				if (m_tsumOffsetY[y][x] < 0.0f)
				{
					m_tsumOffsetY[y][x] += 12.0f;

					if (m_tsumOffsetY[y][x] > 0.0f)
					{
						m_tsumOffsetY[y][x] = 0.0f;
					}

					if (m_tsumOffsetY[y][x] < 0.0f)
					{
						stillFalling = true;
					}
				}
			}
		}

		m_isFalling = stillFalling;

		return;
	}
	CVector2D mouse = CInput::GetMousePoint();

	int x, y;

	// マウスを押した瞬間
	if (PUSH(CInput::eMouseL))
	{
		CVector2D mouse = CInput::GetMousePoint();

		char str[128];

		sprintf_s(str, "Mouse X=%.1f,Y=%.1f\n", mouse.x, mouse.y);
		OutputDebugStringA(str);

		

		if (GetTsumPosition(mouse, x, y))
		{
			char str[128];

			sprintf_s(str, "ツム検知成功 X-%d Y=%d 種類=5d\n", x, y, m_tsumType[y][x]);

			OutputDebugStringA(str);
			m_isDragging = true;

			m_selectType = m_tsumType[y][x];

			m_isSelected[y][x] = true;

			m_selectCount = 1;

			m_startX = x;
			m_startY = y;

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


		//１個だけ選択
		if (m_selectCount == 1)
		{
			m_tsumType[m_startY][m_startX] = -1;
			m_tsumCount[m_startY][m_startX] = 0;
		}

		//２個以上つなげた
		else if (m_selectCount >= 2)
		{
			// 最後につないだ場所
			int targetX = m_lastX;
			int targetY = m_lastY;

			// 選択したツムの合体数を合計する
			int totalTsumCount = 0;

			for (int j = 0; j < ROW; j++)
			{
				for (int i = 0; i < COL; i++)
				{
					if (m_isSelected[j][i])
					{
						totalTsumCount += m_tsumCount[j][i];
					}
				}
			}

			// 最後につないだ場所に合体したツムを残す
			m_tsumType[targetY][targetX] = m_selectType;
			m_tsumCount[targetY][targetX] = totalTsumCount;

			// ほかの選択したツムを消す
			for (int j = 0; j < ROW; j++)
			{
				for (int i = 0; i < COL; i++)
				{
					if (m_isSelected[j][i])
					{
						if (i != targetX || j != targetY)
						{
							m_tsumType[j][i] = -1;
							m_tsumCount[j][i] = 0;
						}
					}
				}
			}
		}
		//ツムの落下・補充
		if (m_selectCount >= 1)
		{
			FallAndRefill();
		}
		//選択状態を解除
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
				startY + y * gapY+m_tsumOffsetY[y][x]
			);

			//消えている場所は描画しない
			if (m_tsumType[y][x] == -1)
			{
				continue;
			}

			// 合体数に応じて大きくする
			float tsumSize = 60.0f + (m_tsumCount[y][x] - 1) * 15.0f;

			// 大きくなりすぎないように制限
			if (tsumSize > 150.0f)
			{
				tsumSize = 150.0f;
			}

			switch (m_tsumType[y][x])
			{
			case 0:
				m_桃太郎.SetSize(tsumSize, tsumSize);
				m_桃太郎.SetCenter(tsumSize / 2, tsumSize / 2);
				m_桃太郎.SetPos(pos);
				m_桃太郎.Draw();
				break;

			case 1:
				m_イヌ.SetSize(tsumSize, tsumSize);
				m_イヌ.SetCenter(tsumSize / 2, tsumSize / 2);
				m_イヌ.SetPos(pos);
				m_イヌ.Draw();
				break;

			case 2:
				m_キジ.SetSize(tsumSize, tsumSize);
				m_キジ.SetCenter(tsumSize / 2, tsumSize / 2);
				m_キジ.SetPos(pos);
				m_キジ.Draw();
				break;

			case 3:
				m_サル.SetSize(tsumSize, tsumSize);
				m_サル.SetCenter(tsumSize / 2, tsumSize / 2);
				m_サル.SetPos(pos);
				m_サル.Draw();
				break;
			}

			if (m_isSelected[y][x])
			{
				Utility::DrawQuad(
					CVector2D(pos.x - size / 2, pos.y - size / 2),
					CVector2D(size, size),
					CVector4D(1, 1, 0, 0.4f));
			}
		}
	}
}
bool Game::GetTsumPosition(CVector2D mouse, int& x, int& y)
{
	float size = 60.0f;

	float startX = 610.0f;
	float startY = 660.0f;

	float gapX = 70.0f;
	float gapY = 78.0f;

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

void Game::FallAndRefill()
{
	// 列ごとに処理
	for (int x = 0; x < COL; x++)
	{
		int writeY = ROW - 1;

		// 下から順番にツムを詰める
		for (int y = ROW - 1; y >= 0; y--)
		{
			if (m_tsumType[y][x] != -1)
			{
				m_tsumType[writeY][x] = m_tsumType[y][x];
				m_tsumCount[writeY][x] = m_tsumCount[y][x];

				// 移動前の位置を記録
				m_tsumOffsetY[writeY][x] =
					(y - writeY) * 78.0f;

				if (writeY != y)
				{
					m_tsumType[y][x] = -1;
					m_tsumCount[y][x] = 0;
				}

				writeY--;
			}
		}

		// 上部に新しいツムを生成
		for (int y = writeY; y >= 0; y--)
		{
			m_tsumType[y][x] = rand() % 4;
			m_tsumCount[y][x] = 1;

			// 盤面の上から落ちてくる
			m_tsumOffsetY[y][x] =
				-(writeY - y + 1) * 78.0f;
		}
	}

	m_isFalling = true;
}