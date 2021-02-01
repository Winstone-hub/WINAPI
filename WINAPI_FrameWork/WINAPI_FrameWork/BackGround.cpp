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
	m_tTransPos.Scale = Vector3(768, 1024);

	m_fAngle = 0.f;
	m_fSpeed = 5.f;
	m_strKey = "BackGround_1";
	/*			   
	m_strKey.push_back(48 + (rand() % 4 + 1));
	*/
}

int BackGround::Progress(void)
{
	m_tTransPos.Position.fY += m_fSpeed;


	if (m_tTransPos.Position.fY >= WINSIZEY)
		m_tTransPos.Position.fY = (-WINSIZEY);


	return 0;
}

void BackGround::Render(HDC _hdc)
{
	//** Menu ��׶��� �̹����� ���ۿ� �����.
	TransparentBlt(_hdc,	  // ������ ���� �׸��� ?!
		m_tTransPos.Position.fX,	// ������ ���� ������ X
		m_tTransPos.Position.fY, 	// ������ ���� ������ Y
		m_tTransPos.Position.fX + m_tTransPos.Scale.fX,	// ������ ���� ���κ� X
		/*m_tTransPos.Position.fY + */m_tTransPos.Scale.fY, // ������ ���� ���κ� Y
		(*m_ImageList)[m_strKey]->GetMemDC(),	// ������ �̹��� (������)
		(int)0 * m_tTransPos.Scale.fX,		// ������ ������ X
		(int)0 * m_tTransPos.Scale.fY,		// ������ ������ Y
		(int)m_tTransPos.Scale.fX, 		// ����� �̹����� ũ�� ��ŭ X
		(int)m_tTransPos.Scale.fY,		// ����� �̹����� ũ�� ��ŭ Y
		RGB(255, 0, 255));		// �ش� ������ ����
}


void BackGround::Release(void)
{

}
