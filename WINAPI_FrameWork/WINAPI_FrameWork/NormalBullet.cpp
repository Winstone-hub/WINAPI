#include "NormalBullet.h"
#include "Object.h"

NormalBullet::NormalBullet()
{

}

NormalBullet::~NormalBullet()
{
	Release();
}


void NormalBullet::Initialize(void)
{
	//** 현재 (NormalBullet) 클레스의 모든 초기값을 설정 한다.
	m_fSpeed = 15.f;
}

void NormalBullet::Progress(Transform & _tTransPos)
{
	//** 
	_tTransPos.Position.fX += cosf(m_fAngle *  PI / 180) * m_fSpeed;
	_tTransPos.Position.fY += -sinf(m_fAngle *  PI / 180) * m_fSpeed;
}

void NormalBullet::Render(HDC _hdc)
{
	//** 
	Ellipse(_hdc,
		int(m_pObject->GetPosition().fX - (m_pObject->GetScale().fX / 2)),
		int(m_pObject->GetPosition().fY - (m_pObject->GetScale().fY / 2)),
		int(m_pObject->GetPosition().fX + (m_pObject->GetScale().fX / 2)),
		int(m_pObject->GetPosition().fY + (m_pObject->GetScale().fY / 2)));
}

void NormalBullet::Release(void)
{

}