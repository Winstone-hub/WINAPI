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
	m_tTransPos.Scale = Vector3(768, 1024);

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
	//** Menu ��׶��� �̹����� ���ۿ� �����.
	TransparentBlt(_hdc,	  // ������ ���� �׸��� ?!
		0,	// ������ ���� ������ X
		0, 	// ������ ���� ������ Y
		WINSIZEX,	// ������ ���� ���κ� X
		WINSIZEY, 	// ������ ���� ���κ� Y
		(*m_ImageList)[m_strKey]->GetMemDC(),	// ������ �̹��� (������)
		(int)m_tTransPos.Position.fX,		// ������ ������ X
		(int)m_tTransPos.Position.fY,		// ������ ������ Y
		(int)m_tTransPos.Scale.fX, 		// ����� �̹����� ũ�� ��ŭ X
		(int)m_tTransPos.Scale.fY,		// ����� �̹����� ũ�� ��ŭ Y
		RGB(255, 0, 255));		// �ش� ������ ����
}


void MenuBack::Release(void)
{

}

