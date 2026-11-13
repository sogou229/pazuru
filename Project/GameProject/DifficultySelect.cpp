#include "DifficultySelect.h"
#include "Game.h"
#include "Title.h"


DifficultySelect::DifficultySelect() :Base(eType_Scene)
{
    m_img.Load("Image/難易度選択（仮）.png");

    m_img.SetSize(1920, 1080);
    m_img.SetCenter(960, 540);
    m_img.SetPos(CVector2D(960, 540));


	m_buttonSize = CVector2D(850, 230);

	m_easyPos = CVector2D(390, 230);
	m_normalPos = CVector2D(390, 465);
	m_hardPos = CVector2D(390, 700);

    m_waitCnt = 5;
}

void DifficultySelect::Update()
{
    //画面切り替え直後の誤操作を防ぐ
    if (m_waitCnt > 0)
    {
        m_waitCnt--;
        return;
    }

	CVector2D mouse = CInput::GetMousePoint();

	if (PUSH(CInput::eMouseL))
	{
		//EASY
		if(mouse.x>=m_easyPos.x&&
		   mouse.x<=m_easyPos.x+m_buttonSize.x&&
		   mouse.y>=m_easyPos.y&&
		   mouse.y<=m_easyPos.y+m_buttonSize.y)
        {
            g_difficulty = eEasy;
            Base::KillAll();
            new Game();
        }

        // NORMAL
        else if (mouse.x >= m_normalPos.x &&
            mouse.x <= m_normalPos.x + m_buttonSize.x &&
            mouse.y >= m_normalPos.y &&
            mouse.y <= m_normalPos.y + m_buttonSize.y)
        {
            g_difficulty = eNormal;
            Base::KillAll();
            new Game();
        }

        // HARD
        else if (mouse.x >= m_hardPos.x &&
            mouse.x <= m_hardPos.x + m_buttonSize.x &&
            mouse.y >= m_hardPos.y &&
            mouse.y <= m_hardPos.y + m_buttonSize.y)
        {
            g_difficulty = eHard;
            Base::KillAll();
            new Game();
        }
    }
}
void DifficultySelect::Draw()
{
    m_img.Draw();
}
