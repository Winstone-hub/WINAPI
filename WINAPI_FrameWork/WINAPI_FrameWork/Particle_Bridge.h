#pragma once
#include "Bridge.h"

class Particle_Bridge : public Bridge
{
protected:
	float m_fSpeed;
public:
	virtual void Initialize(void)PURE;
	virtual void Progress(Transform& _tTransPos)PURE;
	virtual void Render(HDC _hdc)PURE;
	virtual void Release(void)PURE;
public:
	Particle_Bridge() {};
	virtual ~Particle_Bridge() {};
};