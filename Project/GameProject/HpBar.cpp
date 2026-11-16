#include "HpBar.h"

HpBar::HpBar(bool isEnemy, int maxHp):Base(eType_HpBar)
{
    m_isEnemy = isEnemy;

    m_maxHp = maxHp;
    m_hp = maxHp;

    // HPバーのサイズ
    m_size = CVector2D(500, 30);

    // 表示位置
    if (m_isEnemy)
    {
        m_img.Load("Image/EnemyHp.png");

        m_img.SetSize(550, 180);
        m_img.SetCenter(275, 90);
        m_img.SetPos(CVector2D(960, 440));

    }
    else
    {
        m_img.Load("Image/PlayerHp.png");

        m_img.SetSize(600, 250);
        m_img.SetCenter(300, 300);
        m_img.SetPos(CVector2D(960, 540));
    }
}

// ダメージ処理
void HpBar::Damage(int damage)
{
    m_hp -= damage;

    if (m_hp < 0)
    {
        m_hp = 0;
    }
}

// HP設定
void HpBar::SetHp(int hp)
{
    m_hp = hp;

    if (m_hp < 0)
    {
        m_hp = 0;
    }

    if (m_hp > m_maxHp)
    {
        m_hp = m_maxHp;
    }
}

// 現在のHP取得
int HpBar::GetHp()
{
    return m_hp;
}

// 描画処理
void HpBar::Draw()
{
    m_img.Draw();
}