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
	m_Direction = Vector3(0.f, 0.f, 0.f);


	m_fSpeed = 3.f;
	m_strKey = "Player";
	m_bMove = false;
}

void Player::Progress(void)
{
	//CheckKey();

	if (GetAsyncKeyState(VK_RBUTTON) )
	{
		//** 마우스 우클릭 이벤트가 발생하면 플레이어를 움직이게 하기 위함.
		m_bMove = true;

		//** 마우스 좌표를 받아옴.
		GetCursorPos(&m_ptMouse);
		ScreenToClient(g_hWnd, &m_ptMouse);

		//** 마우스 위치에서 플레이어의 위치를 빼 삼각함수의 폭과 높이를 구함.
		m_Direction.fX = m_ptMouse.x - m_tTransPos.Position.fX;
		m_Direction.fY = m_ptMouse.y - m_tTransPos.Position.fY;

		m_TargetPoint = Vector3((float)m_ptMouse.x, (float)m_ptMouse.y);
	}

	if (m_bMove) 
	{
		//** 빗변의 길이를 구함.
		float fLength = sqrt((m_Direction.fX * m_Direction.fX) + (m_Direction.fY * m_Direction.fY));

		//** 폭과 높이보다 항상 큰값인 빗변의 값으로 나누어 정규화 시켜줌.
		m_Direction.fX /= fLength;
		m_Direction.fY /= fLength;

		//** 정규화된 값에 Speed를 곱하여 현재 플레이어의 좌표를 변경함.
		m_tTransPos.Position.fX += m_Direction.fX * m_fSpeed;
		m_tTransPos.Position.fY += m_Direction.fY * m_fSpeed;


		//** 움직이고있는 플레이어 멈추기.
		if (m_TargetPoint.fX + (m_fSpeed / 2.f) > m_tTransPos.Position.fX - (m_fSpeed / 2.f) &&
			 m_TargetPoint.fX - (m_fSpeed / 2.f) < m_tTransPos.Position.fX + (m_fSpeed / 2.f) &&
			 m_TargetPoint.fY + (m_fSpeed / 2.f) > m_tTransPos.Position.fY - (m_fSpeed / 2.f) &&
			 m_TargetPoint.fY - (m_fSpeed / 2.f) < m_tTransPos.Position.fY + (m_fSpeed / 2.f))
		{
			m_bMove = false;
		}
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


