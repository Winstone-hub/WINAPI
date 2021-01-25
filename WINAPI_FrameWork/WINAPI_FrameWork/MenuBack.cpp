#include "MenuBack.h"

MenuBack::MenuBack()
{

}

MenuBack::~MenuBack()
{

}

void MenuBack::Initialize(void)
{
	m_tTransPos.Position = Vector3(0, 0);
	m_tTransPos.Rotation = Vector3(0.f, 0.f, 0.f);
	m_tTransPos.Scale = Vector3(1000, 495);

	m_fAngle = 0.f;
	m_fSpeed = 5.f;
	m_strKey = "MenuBack";
}

int MenuBack::Progress(void)
{
	return 0;
}

void MenuBack::Render(HDC _hdc)
{
	//** Menu 백그라운드 이미지를 버퍼에 출력함.
	TransparentBlt(_hdc,	  // 복사해 넣을 그림판 ?!
		int((WINSIZEX / 2) - (m_tTransPos.Scale.fX / 2)),	// 복사할 영역 시작점 X
		int((WINSIZEY / 2) - (m_tTransPos.Scale.fY / 2)), 	// 복사할 영역 시작점 Y
		(int)m_tTransPos.Scale.fX,	// 복사할 영역 끝부분 X
		(int)m_tTransPos.Scale.fY, 	// 복사할 영역 끝부분 Y
		(*m_ImageList)[m_strKey]->GetMemDC(),	// 복사할 이미지 (복사대상)
		(int)m_tTransPos.Position.fX,		// 복사할 시작점 X
		(int)m_tTransPos.Position.fY,		// 복사할 시작점 Y
		(int)m_tTransPos.Scale.fX, 		// 출력할 이미지의 크기 만큼 X
		(int)m_tTransPos.Scale.fY,		// 출력할 이미지의 크기 만큼 Y
		RGB(255, 0, 255));		// 해당 색상을 제외
}

void MenuBack::Release(void)
{

}

