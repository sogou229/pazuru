#pragma once
#include"Base/Base.h"

class Enemy :public Base 
{
private:

    CImage m_img;

    bool m_flip;
    int m_hp;
    bool m_is_ground;

    int m_down_cnt;
    int m_attack_cnt;
    int m_wait_cnt;
    int m_state;

    // 敵の行動状態
    enum
    {
        eState_Idle,
        eState_Attack,
        eState_Down
    };

public:

    Enemy();

    void Update();
    void Draw();

    // HP取得
    int GetHp();

    // ダメージ処理
    void Damage(int damage);
	//static TexAnimData _anim_data[];
};