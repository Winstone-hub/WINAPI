#include "Player.h"
#include "Bullet.h"

#include "InputManager.h"
#include "ObjectManager.h"
#include "ObjectFactroy.h"

Player::Player()
{
}

Player::~Player()
{
	Release();
}


void Player::Initialize(void)
{
	m_ptMouse = { 0, 0 };
	m_tTransPos.Position = Vector3(WINSIZEX / 2.f, WINSIZEY / 2.f);
	m_tTransPos.Rotation = Vector3(0.f, 0.f, 0.f);
	m_tTransPos.Scale = Vector3(100.f, 100.f);

	m_TargetPoint = Vector3(0.f, 0.f, 0.f);
	m_Direction = Vector3(0.f, 0.f, 0.f);
	m_LinePoint = Vector3(0.f, 0.f, 0.f);

	m_fAngle = 0.f;
	m_fSpeed = 3.f;
	m_strKey = "Player";
	m_bMove = false;
}

void Player::Progress(void)
{
	CheckKey();

	m_LinePoint.fX = m_tTransPos.Position.fX + cosf(m_fAngle *  PI / 180) * 100;
	m_LinePoint.fY = m_tTransPos.Position.fY + -sinf(m_fAngle *  PI / 180) * 100;
	
	if (m_bMove) 
	{
		//** ������ ���̸� ����.
		float fLength = sqrt((m_Direction.fX * m_Direction.fX) + (m_Direction.fY * m_Direction.fY));

		//** ���� ���̺��� �׻� ū���� ������ ������ ������ ����ȭ ������.
		m_Direction.fX /= fLength;
		m_Direction.fY /= fLength;

		//** ����ȭ�� ���� Speed�� ���Ͽ� ���� �÷��̾��� ��ǥ�� ������.
		m_tTransPos.Position.fX += m_Direction.fX * m_fSpeed;
		m_tTransPos.Position.fY += m_Direction.fY * m_fSpeed;


		//** �����̰��ִ� �÷��̾� ���߱�.
		if (m_TargetPoint.fX + (m_fSpeed / 2.f) > m_tTransPos.Position.fX - (m_fSpeed / 2.f) &&
			 m_TargetPoint.fX - (m_fSpeed / 2.f) < m_tTransPos.Position.fX + (m_fSpeed / 2.f) &&
			 m_TargetPoint.fY + (m_fSpeed / 2.f) > m_tTransPos.Position.fY - (m_fSpeed / 2.f) &&
			 m_TargetPoint.fY - (m_fSpeed / 2.f) < m_tTransPos.Position.fY + (m_fSpeed / 2.f))
		{
			m_bMove = false;
		}
	}
}

void Player::Render(HDC _hdc )
{
	Ellipse(_hdc,
		int(m_tTransPos.Position.fX - (m_tTransPos.Scale.fX / 2)),
		int(m_tTransPos.Position.fY - (m_tTransPos.Scale.fY / 2)),
		int(m_tTransPos.Position.fX + (m_tTransPos.Scale.fX / 2)),
		int(m_tTransPos.Position.fY + (m_tTransPos.Scale.fY / 2)));

	MoveToEx(_hdc, m_tTransPos.Position.fX, m_tTransPos.Position.fY, NULL);

	LineTo(_hdc, m_LinePoint.fX, m_LinePoint.fY);
}

void Player::Release(void)
{

}

void Player::CheckKey()
{
	DWORD dwKey = InputManager::GetInstance()->GetKey();

	if (KEY_UP & dwKey)
	{
		// m_tTransPos.Position.fY -= m_fSpeed;

		m_tTransPos.Position.fX +=cosf(m_fAngle *  PI / 180) * m_fSpeed;
		m_tTransPos.Position.fY +=-sinf(m_fAngle *  PI / 180) * m_fSpeed;
	}
	if (KEY_DOWN & dwKey)
	{
		// m_tTransPos.Position.fY += m_fSpeed;

		m_tTransPos.Position.fX -= cosf(m_fAngle *  PI / 180) * m_fSpeed;
		m_tTransPos.Position.fY -= -sinf(m_fAngle *  PI / 180) * m_fSpeed;
	}
	
	if (KEY_LEFT & dwKey)
	{
		//m_tTransPos.Position.fX -= 5;
		m_fAngle += 5.f;
	}
	if (KEY_RIGHT & dwKey)
	{
		//m_tTransPos.Position.fX += 5;
		m_fAngle -= 5.f;
	}

	if (KEY_SPACE & dwKey)
	{
		ObjectManager::GetInstance()->AddObject("Bullet",
			ObjectFactroy<Bullet>::CreateObject(m_tTransPos.Position.fX, m_tTransPos.Position.fY) );
	}

	if (KEY_RBUTTON & dwKey)
	{
		//** ���콺 ��Ŭ�� �̺�Ʈ�� �߻��ϸ� �÷��̾ �����̰� �ϱ� ����.
		m_bMove = true;

		//** ���콺 ��ǥ�� �޾ƿ�.
		GetCursorPos(&m_ptMouse);
		ScreenToClient(g_hWnd, &m_ptMouse);

		//** ���콺 ��ġ���� �÷��̾��� ��ġ�� �� �ﰢ�Լ��� ���� ���̸� ����.
		m_Direction.fX = m_ptMouse.x - m_tTransPos.Position.fX;
		m_Direction.fY = m_ptMouse.y - m_tTransPos.Position.fY;

		m_TargetPoint = Vector3((float)m_ptMouse.x, (float)m_ptMouse.y);
	}
}


