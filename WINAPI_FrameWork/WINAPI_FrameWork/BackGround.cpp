#include "BackGround.h"


BackGround::BackGround()
{

}

BackGround::~BackGround()
{

}


void BackGround::Initialize(void)
{
	m_tTransPos.Position = Vector3(0, 0);
	m_tTransPos.Rotation = Vector3(0.f, 0.f, 0.f);
	m_tTransPos.Scale = Vector3(1280, 720);

	m_fAngle = 0.f;
	m_fSpeed = 5.f;
	m_strKey = "BackGround";
}

int BackGround::Progress(void)
{
	m_tTransPos.Position.fX += m_fSpeed;

	if (m_tTransPos.Position.fX >= m_tTransPos.Scale.fX)
		m_tTransPos.Position.fX = 0;


	return 0;
}

void BackGround::Render(HDC _hdc)
{
	//** �������� �̹����� ���ۿ� �����.
	TransparentBlt(_hdc,	  // ������ ���� �׸��� ?!
		(WINSIZEX / 2) - (1280 / 2),	// ������ ���� ������ X
		(WINSIZEY / 2) - (720 / 2), 	// ������ ���� ������ Y
		(int)m_tTransPos.Scale.fX,	// ������ ���� ���κ� X
		(int)m_tTransPos.Scale.fY, 	// ������ ���� ���κ� Y
		(*m_ImageList)[m_strKey]->GetMemDC(),	// ������ �̹��� (������)
		(int)m_tTransPos.Position.fX,		// ������ ������ X
		(int)m_tTransPos.Position.fY,		// ������ ������ Y
		(int)m_tTransPos.Scale.fX, 		// ����� �̹����� ũ�� ��ŭ X
		(int)m_tTransPos.Scale.fY,		// ����� �̹����� ũ�� ��ŭ Y
		RGB(255, 0, 255));		// �ش� ������ ����
}

void BackGround::Release(void)
{

}