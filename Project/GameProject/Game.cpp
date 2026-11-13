#include"Game.h"
#include"Title.h"
#include"Enemy.h"
#include"Player.h"
//#include"GameClear.h"
//#include"GameOver.h"
//#include"HpBar.h"

eDifficulty g_difficulty = eNormal;

Game::Game() :Base(eType_Scene)
{
	new Enemy(CVector2D(960, 540));
}
void Game::Update()
{


}