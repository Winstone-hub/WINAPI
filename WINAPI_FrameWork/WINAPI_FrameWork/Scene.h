#pragma once
#include "Include.h"


class Bitmap;
class Scene
{
protected:
	map<string, Bitmap*>	m_ImageList;
public:
	virtual void Initialize()PURE;
	virtual int Progress()PURE;
	virtual void Render(HDC _hdc)PURE;
	virtual void Release()PURE;
public:
	Scene();
	virtual ~Scene();
};

