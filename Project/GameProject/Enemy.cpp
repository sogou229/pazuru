#include"Enemy.h"
#include "Game.h"

// コンストラクタ
Enemy::Enemy() : Base(eType_Enemy)
{
    // 画像設定
    m_img = COPY_RESOURCE("Enemy", CImage);

    m_img.SetCenter(200, 250);
    m_img.SetSize(400, 400);
    m_img.SetPos(CVector2D(1400, 700));

    // 初期設定
    m_flip = false;
    m_is_ground = true;

    m_hp = 100;

    m_down_cnt = 0;
    m_attack_cnt = 0;
    m_wait_cnt = 0;

    m_state = eState_Idle;

    // 難易度によるHP変更
    if (g_difficulty == eEasy)
    {
        m_hp = 60;
    }
    else if (g_difficulty == eNormal)
    {
        m_hp = 100;
    }
    else if (g_difficulty == eHard)
    {
        m_hp = 180;
    }
}

// 更新処理
void Enemy::Update()
{
    // 待機状態
    if (m_state == eState_Idle)
    {
        m_wait_cnt++;

        // 60フレーム待機したら攻撃
        if (m_wait_cnt >= 60)
        {
            m_state = eState_Attack;
            m_wait_cnt = 0;
            m_attack_cnt = 0;
        }
    }

    // 攻撃状態
    else if (m_state == eState_Attack)
    {
        m_attack_cnt++;

        // 18フレーム経過したら待機
        if (m_attack_cnt >= 18)
        {
            m_state = eState_Idle;
            m_attack_cnt = 0;
        }
    }

    // ダウン状態
    else if (m_state == eState_Down)
    {
        m_down_cnt++;

        // 60フレーム経過したら消す
        if (m_down_cnt >= 60)
        {
            SetKill();
        }
    }
}

// 描画処理
void Enemy::Draw()
{
    m_img.Draw();
}

// HP取得
int Enemy::GetHp()
{
    return m_hp;
}

// ダメージ処理
void Enemy::Damage(int damage)
{
    if (m_state == eState_Down)
    {
        return;
    }

    m_hp -= damage;

    if (m_hp <= 0)
    {
        m_hp = 0;

        m_state = eState_Down;
        m_down_cnt = 0;
    }
}


