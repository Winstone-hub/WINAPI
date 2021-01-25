#include "Button.h"


Button::Button()
{

}

Button::~Button()
{

}


void Button::Initialize(void)
{
	m_tTransPos.Position = Vector3(WINSIZEX / 2, WINSIZEX / 2);
	m_tTransPos.Rotation = Vector3(0.f, 0.f, 0.f);
	m_tTransPos.Scale = Vector3(1253, 1300 / 2);

	m_iScene = 0;
	m_fAngle = 0.f;
	m_fSpeed = 5.f;
	m_strKey = "PlayButton";
}

int Button::Progress(void)
{
	return 0;
}

void Button::Render(HDC _hdc)
{
	//** Menu Button �̹����� ���ۿ� �����.
	TransparentBlt(_hdc,	  // ������ ���� �׸��� ?!
		int(m_tTransPos.Position.fX),	// ������ ���� ������ X
		int(m_tTransPos.Position.fY), 	// ������ ���� ������ Y
		(int)m_tTransPos.Scale.fX,	// ������ ���� ���κ� X
		(int)m_tTransPos.Scale.fY, 	// ������ ���� ���κ� Y
		(*m_ImageList)[m_strKey]->GetMemDC(),	// ������ �̹��� (������)
		(int)m_tTransPos.Position.fX,		// ������ ������ X
		(int)m_tTransPos.Position.fY,		// ������ ������ Y
		int(m_tTransPos.Scale.fX), 		// ����� �̹����� ũ�� ��ŭ X
		int(m_tTransPos.Scale.fY * m_iScene),		// ����� �̹����� ũ�� ��ŭ Y
		RGB(255, 0, 255));		// �ش� ������ ����
}

void Button::Release(void)
{

}
