#pragma once
#include "Scene.h"

class Object;
class Logo : public Scene
{
private:
	//HWND		m_hVideo;
	Object* m_pBackGround[2];
	Object* m_pLogoObject;
	vector<Object*> m_pButtonList;
public:
	virtual void Initialize(void)override;
	virtual int Progress(void)override;
	virtual void Render(HDC _hdc)override;
	virtual void Release(void)override;
public:
	Logo();
	virtual ~Logo();
};

