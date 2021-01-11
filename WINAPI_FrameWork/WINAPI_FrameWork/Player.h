#pragma once
#include "Object.h"

class Player : public Object
{
private:
	POINT m_ptMouse;
	bool m_bMove;
public:
	virtual void Initialize(void)override;
	virtual void Progress(void)override;
	virtual void Render(HDC _hdc)override;
	virtual void Release(void)override;
public:
	void CheckKey();
public:
	Player();
	virtual ~Player();
};

