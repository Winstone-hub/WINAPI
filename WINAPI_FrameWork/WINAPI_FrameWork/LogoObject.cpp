#include "LogoObject.h"


LogoObject::LogoObject()
{

}

LogoObject::~LogoObject()
{

}


void LogoObject::Initialize(void)
{
	m_tTransPos.Position = Vector3(0, 0);
	m_tTransPos.Rotation = Vector3(0.f, 0.f, 0.f);
	m_tTransPos.Scale = Vector3(483, 289);
}

int LogoObject::Progress(void)
{

	return 0;
}

void LogoObject::Render(HDC _hdc)
{
	/*
	//** Menu 백그라운드 이미지를 버퍼에 출력함.
	TransparentBlt(_hdc,	  // 복사해 넣을 그림판 ?!
		int(m_tTransPos.Position.fX - int(m_tTransPos.Scale.fX / 2)),	// 복사할 영역 시작점 X
		int(m_tTransPos.Position.fY - int(m_tTransPos.Scale.fY / 2)), 	// 복사할 영역 시작점 Y
		(int)m_tTransPos.Scale.fX,	// 복사할 영역 끝부분 X
		(int)m_tTransPos.Scale.fY, 	// 복사할 영역 끝부분 Y
		(*m_ImageList)[m_strKey]->GetMemDC(),	// 복사할 이미지 (복사대상)
		0,		// 복사할 시작점 X
		0,		// 복사할 시작점 Y
		(int)m_tTransPos.Scale.fX, 		// 출력할 이미지의 크기 만큼 X
		(int)m_tTransPos.Scale.fY,		// 출력할 이미지의 크기 만큼 Y
		RGB(255, 255, 255));		// 해당 색상을 제외
	*/
	
	BLENDFUNCTION bf; // 이름은 FUNCTION이지만 구조체입니다

	ZeroMemory(&bf, sizeof(BLENDFUNCTION));  //멤버들을 모두 0으로...
	bf.BlendOp = AC_SRC_OVER;

	bf.SourceConstantAlpha = 100; //0~255 값을 가지는 투명도

	AlphaBlend(_hdc,		// 그려질 위치
		int(m_tTransPos.Position.fX - (m_tTransPos.Scale.fX / 2)),		// 이미지를 넣을곳 X 
		int(m_tTransPos.Position.fY - (m_tTransPos.Scale.fY / 2)),		// 이미지를 넣을곳 Y
		(int)m_tTransPos.Scale.fX, (int)m_tTransPos.Scale.fY,		// 현재 스케일 값 만큼
		(*m_ImageList)[m_strKey]->GetMemDC(),		// 담을 이미지 (복사 대상)
		int(0 * m_tTransPos.Scale.fX),		//	복사 시작 위치 X
		int(0 * m_tTransPos.Scale.fY),		//  복사 시작 위치 Y
		(int)m_tTransPos.Scale.fX, (int)m_tTransPos.Scale.fY,		// 복사할 크기값 만큼
		bf);
}

void LogoObject::Release(void)
{

}
