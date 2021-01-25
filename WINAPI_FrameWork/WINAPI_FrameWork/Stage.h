#pragma once
#include "Scene.h"


class Stage : public Scene
{
private:
	Bitmap* m_pBackBuffer;
public:
	virtual void Initialize(void)override;
	virtual void Progress(void)override;
	virtual void Render(HDC _hdc)override;
	virtual void Release(void)override;
public:
	Stage();
	virtual ~Stage();
};

