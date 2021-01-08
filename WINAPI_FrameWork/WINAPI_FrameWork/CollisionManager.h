#pragma once
#include "Include.h"
#include "Object.h"

class CollisionManager
{
public:
	static bool Collision(Object* _pTempObj, Object* _pDestObj)
	{
		float fX = _pTempObj->GetPosition().fX - _pDestObj->GetPosition().fX;
		float fY = _pTempObj->GetPosition().fY - _pDestObj->GetPosition().fY;

		float fSum = (_pTempObj->GetScale().fX / 2) + (_pDestObj->GetScale().fX / 2);

		float fLen = sqrt((fX * fX) + (fY * fY));

		if (fSum > fLen)
			return true;

		return false;
	}

private:
	CollisionManager();
public:
	~CollisionManager();
};

