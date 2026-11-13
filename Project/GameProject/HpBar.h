#pragma once
#include "Base/Base.h"

class HpBar :public Base
{
 private:
	int m_maxHp;
	int m_hp;

	bool m_isEnemy;

	CVector2D m_pos;
	CVector2D m_size;

public:
	HpBar(bool isEnemy, int maxHp);

	void Damage(int damage);
	void SetHp(int hp);
	int GetHp();

	void Draw();
};