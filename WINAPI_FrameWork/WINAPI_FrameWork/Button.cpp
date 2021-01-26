#include "Button.h"
#include "CollisionManager.h"
#include "InputManager.h"


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

		if (InputManager::GetInstance()->GetKey() & KEY_LBUTTON)
		{
			if (m_strKey == "PlayButton")
				return 1;

			else if (m_strKey == "Option")
				return 2;

			else if (m_strKey == "Exit")
				return 3;
		}
	}

	return 0;
}

void Button::Render(HDC _hdc)
{
	//** Menu Button �̹����� ���ۿ� �����.
	TransparentBlt(_hdc,	  // ������ ���� �׸��� ?!
		int(m_tTransPos.Position.fX - int(m_tTransPos.Scale.fX / 2)),	// ������ ���� ������ X
		int(m_tTransPos.Position.fY - int(m_tTransPos.Scale.fY / 2)), 	// ������ ���� ������ Y
		(int)m_tTransPos.Scale.fX,	// ������ ���� ���κ� X
		(int)m_tTransPos.Scale.fY, 	// ������ ���� ���κ� Y
		(*m_ImageList)[m_strKey]->GetMemDC(),	// ������ �̹��� (������)
		(int)m_tTransPos.Scale.fX * m_iScene,	// ������ ������ X
		0,										// ������ ������ Y
		int(m_tTransPos.Scale.fX), 		// ����� �̹����� ũ�� ��ŭ X
		int(m_tTransPos.Scale.fY),		// ����� �̹����� ũ�� ��ŭ Y
		RGB(255, 0, 255));		// �ش� ������ ����
}

void Button::Release(void)
{

}
