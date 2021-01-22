#pragma once
#include "Object.h"

class BackGround : public Object
{
public:
	virtual void Initialize(void)override;
	virtual void Progress(void)override;
	virtual void Render(HDC _hdc)override;
	virtual void Release(void)override;
public:
	BackGround();
	virtual ~BackGround();
};

