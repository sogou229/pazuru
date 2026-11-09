#include "Title.h"
//#include "Game.h"

Title::Title():Base(eType_Scene)
{
	pushMouse = true;
    
	m_img=COPY_RESOURCE("Title",CImage);

	m_img.SetSize(1920,1080);
	m_img.SetCenter(960, 540);
	m_img.SetPos(CVector2D(960, 540));

}
void Title::Update()
{
	if (PUSH(CInput::eMouseL)) 
	{
		Base::KillAll();

		//new Game();
	}
}
void Title::Draw()
{
	/*if (m_start)
	{
		return;
	}
	m_img.SetPos(CVector2D(960, 540));

	m_img.SetPos(m_pos);
	*/m_img.Draw();
}