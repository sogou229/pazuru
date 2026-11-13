#pragma once
#include"Base/Base.h"

class DifficultySelect :public Base
{
 private:
     CImage m_img;
     // ボタンの位置とサイズ
     CVector2D m_easyPos;
     CVector2D m_normalPos;
     CVector2D m_hardPos;

     CVector2D m_buttonSize;
     int m_waitCnt;
public:

    DifficultySelect();

    void Update();
    void Draw();
};