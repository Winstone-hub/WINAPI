#pragma once

template <typename T>
class ObjectFactroy
{
public:
	static Object* CreateObject()
	{
		Object* pObj = new T;
		pObj->Initialize();

		return pObj;
	}

	static Object* CreateObject(float _fx, float _fy)
	{
		Object* pObj = new T;
		pObj->Initialize();

		pObj->SetPosition(_fx, _fy);

		return pObj;
	}
};