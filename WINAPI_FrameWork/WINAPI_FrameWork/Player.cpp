#include "Player.h"
#include "InputManager.h"


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

	m_strKey = "Player";
	m_bMove = false;
}

void Player::Progress(void)
{
	//CheckKey();

	if (GetAsyncKeyState(VK_RBUTTON) && !m_bMove)
	{
		m_bMove = true;

		GetCursorPos(&m_ptMouse);
		ScreenToClient(g_hWnd, &m_ptMouse);

		m_TargetPoint.fX = m_ptMouse.x - m_tTransPos.Position.fX;
		m_TargetPoint.fY = m_ptMouse.y - m_tTransPos.Position.fY;
	}

	if (m_bMove) 
	{
		float fLength = sqrt((m_TargetPoint.fX * m_TargetPoint.fX) + (m_TargetPoint.fY * m_TargetPoint.fY));

		m_TargetPoint.fX /= fLength;
		m_TargetPoint.fY /= fLength;

		m_tTransPos.Position.fX += m_TargetPoint.fX * 3;
		m_tTransPos.Position.fY += m_TargetPoint.fY * 3;


		//** 움직이고있는 플레이어 멈추기.


	}
}

void Player::Render(HDC _hdc)
{
	Ellipse(_hdc,
		int(m_tTransPos.Position.fX - (m_tTransPos.Scale.fX / 2)),
		int(m_tTransPos.Position.fY - (m_tTransPos.Scale.fY / 2)),
		int(m_tTransPos.Position.fX + (m_tTransPos.Scale.fX / 2)),
		int(m_tTransPos.Position.fY + (m_tTransPos.Scale.fY / 2)) );
}

void Player::Release(void)
{

}

void Player::CheckKey()
{
	DWORD dwKey = InputManager::GetInstance()->GetKey();

	if (KEY_UP & dwKey)
	{
		m_tTransPos.Position.fY -= 5;
	}
	if (KEY_DOWN & dwKey)
	{
		m_tTransPos.Position.fY += 5;
	}
	if (KEY_LEFT & dwKey)
	{
		m_tTransPos.Position.fX -= 5;
	}
	if (KEY_RIGHT & dwKey)
	{
		m_tTransPos.Position.fX += 5;
	}
	if (KEY_SPACE & dwKey)
	{

	}
}


