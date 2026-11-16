#include"Game.h"
#include"Title.h"
#include"Enemy.h"
#include"Player.h"
#include"HpBar.h"
//#include"GameClear.h"
//#include"GameOver.h"


eDifficulty g_difficulty = eNormal;

Game::Game() :Base(eType_Scene)
{
	//”Õ–Ê‰æ‘œ
	m_img.Load("Image/”Õ–Ê.png");

	m_img.SetSize(960, 1080);
	m_img.SetCenter(590, 660);
	m_img.SetPos(CVector2D(960, 540));

	new HpBar(false, 100);
	new HpBar(true, 100);

	new Enemy(CVector2D(960, 540));
}
void Game::Update()
{


}
void Game::Draw()
{
	m_img.Draw();
}