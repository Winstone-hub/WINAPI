#include "Bullet.h"

Bullet::Bullet()
{

}

Bullet::~Bullet()
{

}


void Bullet::Initialize(void)
{
	m_tTransPos.Position = Vector3(0.f, 0.f);
	m_tTransPos.Rotation = Vector3(0.f, 0.f, 0.f);
	m_tTransPos.Scale = Vector3(30.f, 30.f);

	m_fAngle = 0.f;
	m_strKey = "Bullet";
	m_fSpeed = 15.f;
}

void Bullet::Progress(void)
{
	//m_tTransPos.Position.fY -= m_fSpeed;

	m_tTransPos.Position.fX += cosf(m_fX *  PI / 180) * m_fSpeed;
	m_tTransPos.Position.fY += -sinf(m_fY *  PI / 180) * m_fSpeed;
}

void Bullet::Render(HDC _hdc)
{
	Ellipse(_hdc,
		int(m_tTransPos.Position.fX - (m_tTransPos.Scale.fX / 2)),
		int(m_tTransPos.Position.fY - (m_tTransPos.Scale.fY / 2)),
		int(m_tTransPos.Position.fX + (m_tTransPos.Scale.fX / 2)),
		int(m_tTransPos.Position.fY + (m_tTransPos.Scale.fY / 2)));
}

void Bullet::Release(void)
{

}

