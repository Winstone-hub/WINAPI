#pragma once
#include "Scene.h"

class Object;
class Menu : public Scene
{
private:
	Object* m_pButton[3];
public:
	virtual void Initialize(void)override;
	virtual int Progress(void)override;
	virtual void Render(HDC _hdc)override;
	virtual void Release(void)override;
public:
	Menu();
	virtual ~Menu();
};

