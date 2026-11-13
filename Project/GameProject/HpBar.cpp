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
        // 敵HP
        m_pos = CVector2D(1200, 30);
    }
    else
    {
        // プレイヤーHP
        m_pos = CVector2D(100, 30);
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
    if (m_maxHp <= 0)
    {
        return;
    }

    float rate = (float)m_hp / m_maxHp;

    // 背景
    Utility::DrawQuad(
        m_pos,
        m_size,
        CVector4D(0, 0, 0, 1)
    );

    // HPゲージの幅
    CVector2D gaugeSize(
        m_size.x * rate,
        m_size.y
    );

    CVector4D color;

    if (m_isEnemy)
    {
        // 敵は紫
        color = CVector4D(0.6f, 0.1f, 0.9f, 1);
    }
    else
    {
        // プレイヤーはオレンジ
        color = CVector4D(1.0f, 0.5f, 0.0f, 1);
    }

    Utility::DrawQuad(
        m_pos,
        gaugeSize,
        color
    );
}