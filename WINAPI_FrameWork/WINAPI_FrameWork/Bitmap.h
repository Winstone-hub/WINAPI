#pragma once
#include "Include.h"

class Bitmap
{
private:
	HDC				m_hdc, m_MemDC;
	HBITMAP   m_bitmap, m_Oldbitmap;
public:
	Bitmap* LoadBmp(PTCHAR _FileName);
	void Release();
public:
	Bitmap();
	~Bitmap();
};

