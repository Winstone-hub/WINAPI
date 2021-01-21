#pragma once
#include "Include.h"
#include "Bitmap.h"

class Object
{
protected:
	Transform m_tTransPos;
	Frame m_tFrame;

	string m_strKey;

	float m_fSpeed;
	float m_fAngle;

	ULONGLONG m_dwFrameTime;

	static map<string, Bitmap*>* m_ImageList;
public:
	static void SetImageList(map<string, Bitmap*>* _ImageList)
	{
		m_ImageList = _ImageList;
	}
public:
	virtual void Initialize()PURE;
	virtual void Progress()PURE;
	virtual void Render(HDC _hdc)PURE;
	virtual void Release()PURE;
public:
	string GetKey() { return m_strKey; }
	Vector3 GetPosition() { return m_tTransPos.Position; }
	Vector3 GetScale() { return m_tTransPos.Scale; }
	float GetAngle() { return m_fAngle; }
	void SetAngle(float _Angle) { m_fAngle = _Angle; }

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

