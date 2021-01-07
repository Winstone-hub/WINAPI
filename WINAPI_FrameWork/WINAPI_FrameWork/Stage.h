#pragma once
#include "Scene.h"

class Object;
class Stage : public Scene
{
private:
	Object* m_pObject1;
	Object* m_pObject2;
public:
	virtual void Initialize(void)override;
	virtual void Progress(void)override;
	virtual void Render(HDC _hdc)override;
	virtual void Release(void)override;
public:
	Stage();
	virtual ~Stage();
};

