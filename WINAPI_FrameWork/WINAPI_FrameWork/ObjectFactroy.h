#pragma once
#include "Bridge.h"
#include "Object.h"

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

	static Object* CreateObject(string _strKey)
	{
		Object* pObj = new T;
		pObj->Initialize();
		pObj->SetKey(_strKey);
		
		return pObj;
	}

	static Object* CreateObject(float _fx, float _fy)
	{
		Object* pObj = new T;
		pObj->Initialize();

		pObj->SetPosition(_fx, _fy);

		return pObj;
	}

	static Object* CreateObject(float _fx, float _fy, string _str)
	{
		Object* pObj = new T;
		pObj->Initialize();

		pObj->SetPosition(_fx, _fy);
		pObj->SetKey(_str);

		return pObj;
	}

	static Object* CreateObject(float _fx, float _fy, Bridge* _pBridge)
	{
		Object* pObj = new T;

		pObj->Initialize();
		pObj->SetPosition(_fx, _fy);


		_pBridge->Initialize();
		_pBridge->SetObject(pObj);


		((T*)pObj)->SetBridge(_pBridge);


		return pObj;
	}
};