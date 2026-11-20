#pragma once
#include<string>
#include<windows.h>
#include<gl/GL.h>

class CText
{
 public:
	 static void Init(HDC hdc);
	 static void Draw(float x, float y, const std::string& text);
	 static void Release();
private:
	static unsigned int m_fontBase;
};