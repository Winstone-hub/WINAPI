#include "Button.h"
#include "CollisionManager.h"

Button::Button()
{

}

Button::~Button()
{

}


void Button::Initialize(void)
{
	m_tTransPos.Position = Vector3(WINSIZEX / 2, WINSIZEY / 2);
	m_tTransPos.Rotation = Vector3(0.f, 0.f, 0.f);
	m_tTransPos.Scale = Vector3(749 / 8, 97);

	m_iScene = 0;
	m_fAngle = 0.f;
	m_fSpeed = 5.f;
	m_strKey = "PlayButton";
}

int Button::Progress(void)
{
	POINT ptMouse;

	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	float fX = ptMouse.x - m_tTransPos.Position.fX;
	float fY = ptMouse.y - m_tTransPos.Position.fY;

	float fSum = 50;

	float fLen = sqrt((fX * fX) + (fY * fY));

	if (fSum > fLen)
	{
		m_iScene++;

		if (m_iScene > 8)
			m_iScene = 0;
	}

	return 0;
}

void Button::Render(HDC _hdc)
{
	//** Menu Button 이미지를 버퍼에 출력함.
	TransparentBlt(_hdc,	  // 복사해 넣을 그림판 ?!
		int(m_tTransPos.Position.fX - int(m_tTransPos.Scale.fX / 2)),	// 복사할 영역 시작점 X
		int(m_tTransPos.Position.fY - int(m_tTransPos.Scale.fY / 2)), 	// 복사할 영역 시작점 Y
		(int)m_tTransPos.Scale.fX,	// 복사할 영역 끝부분 X
		(int)m_tTransPos.Scale.fY, 	// 복사할 영역 끝부분 Y
		(*m_ImageList)[m_strKey]->GetMemDC(),	// 복사할 이미지 (복사대상)
		(int)m_tTransPos.Scale.fX * m_iScene,	// 복사할 시작점 X
		0,										// 복사할 시작점 Y
		int(m_tTransPos.Scale.fX), 		// 출력할 이미지의 크기 만큼 X
		int(m_tTransPos.Scale.fY),		// 출력할 이미지의 크기 만큼 Y
		RGB(255, 0, 255));		// 해당 색상을 제외
}

void Button::Release(void)
{

}
