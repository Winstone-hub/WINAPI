#pragma once
#include "Include.h"


class Bitmap;
class Scene
{
protected:
	map<string, Bitmap*>* m_pImageList;
public:
	virtual void Initialize()PURE;
	virtual void Progress()PURE;
	virtual void Render(HDC _hdc)PURE;
	virtual void Release()PURE;
public:
	Scene();
	virtual ~Scene();
};

