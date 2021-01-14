#pragma once
#include "Object.h"

class Bullet : public Object
{
private:
	float m_fX;
	float m_fY;
public:
	virtual void Initialize(void)override;
	virtual void Progress(void)override;
	virtual void Render(HDC _hdc)override;
	virtual void Release(void)override;
public:
	void SetBulletAngle()
	{
		m_fX = m_fAngle + ((rand() % 60) - 30);
		m_fY = m_fAngle + ((rand() % 60) - 30);
	}
public:
	Bullet();
	virtual ~Bullet();
};

