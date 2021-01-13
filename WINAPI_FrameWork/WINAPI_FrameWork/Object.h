#pragma once
#include "Include.h"

class Object
{
protected:
	Transform m_tTransPos;
	string m_strKey;
	float m_fSpeed;
	float m_fAngle;
public:
	virtual void Initialize()PURE;
	virtual void Progress()PURE;
	virtual void Render(HDC _hdc)PURE;
	virtual void Release()PURE;

public:
	string GetKey() { return m_strKey; }
	Vector3 GetPosition() { return m_tTransPos.Position; }
	Vector3 GetScale() { return m_tTransPos.Scale; }
	
	void SetPosition(float _fx, float _fy)
	{
		m_tTransPos.Position.fX = _fx;
		m_tTransPos.Position.fY = _fy;
	}

	void SetScale(float _fx, float _fy)
	{
		m_tTransPos.Scale.fX = _fx;
		m_tTransPos.Scale.fY = _fy;
	}

public:
	Object();
	virtual ~Object();
};

