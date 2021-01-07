#pragma once
#include "Object.h"

class Monster : public Object
{
public:
	virtual void Initialize(void)override;
	virtual void Progress(void)override;
	virtual void Render(HDC _hdc)override;
	virtual void Release(void)override;

public:
	Monster();
	virtual ~Monster();
};

