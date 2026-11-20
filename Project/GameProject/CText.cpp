#include"CText.h"

unsigned int CText::m_fontBase = 0;

void CText::Init(HDC hdc)
{
	HFONT font = CreateFontA(
		28, 0, 0, 0, FW_NORMAL,
		FALSE, FALSE, FALSE,
		SHIFTJIS_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		ANTIALIASED_QUALITY,
		FF_DONTCARE,
		"MS Gothic");

	HGDIOBJ oldFont = SelectObject(hdc, font);

	m_fontBase = glGenLists(256);

	wglUseFontBitmapsA(hdc, 0, 256, m_fontBase);

	SelectObject(hdc, oldFont);
	DeleteObject(font);
}
void CText::Draw(float x, float y, const std::string& text)
{
	if (m_fontBase == 0)return;

	glRasterPos2f(x, y);

	glListBase(m_fontBase);
	glCallLists(
		(GLsizei)text.length(),
		GL_UNSIGNED_BYTE,
		text.c_str()
	);
}
void CText::Release()
{
	if (m_fontBase != 0)
	{
		glDeleteLists(m_fontBase, 256);
		m_fontBase = 0;
	}
}