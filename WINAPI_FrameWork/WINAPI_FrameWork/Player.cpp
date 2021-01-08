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
	m_tTransPos.Position = Vector3(WINSIZEX / 2.f, WINSIZEY / 2.f);
	m_tTransPos.Rotation = Vector3(0.f, 0.f, 0.f);
	m_tTransPos.Scale = Vector3(100.f, 100.f);

	m_strKey = "Player";
}

void Player::Progress(void)
{
	/*
	POINT ptMouse;

	GetCursorPos(&ptMouse);

	ScreenToClient(g_hWnd, &ptMouse);
	
	m_tTransPos.Position = Vector3(ptMouse.x, ptMouse.y);
	*/
	 
	
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


