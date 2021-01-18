#pragma once
#include "Object.h"

class Player : public Object
{
private:
	POINT m_ptMouse;
	bool m_bMove;

	Vector3 m_Direction;
	Vector3 m_TargetPoint;

	Vector3 m_LinePoint;
	bool m_bJump;

	float m_fOldY;
	float m_fTime;
public:
	virtual void Initialize(void)override;
	virtual void Progress(void)override;
	virtual void Render(HDC _hdc)override;
	virtual void Release(void)override;
public:
	template <typename T>
	Object* CreateBullet(void);

public:
	void CheckKey();
	void SetMoveFalse()
	{
		m_bMove = false;
	}

	

public:
	Player();
	virtual ~Player();
};

