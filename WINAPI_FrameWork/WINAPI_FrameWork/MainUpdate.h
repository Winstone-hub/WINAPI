#pragma once
#include "Include.h"


class MainUpdate
{
private:
	HDC m_hdc;
public:
	void Initialize(void);
	void Progress(void);
	void Render(void);
	void Release(void);

public:
	MainUpdate();
	~MainUpdate();
};

/***********************************************************
*		** Schedule board **
* 1. DC �߰� �� ����� �߰�. �ϰ� ��� ���� ����.
* 2. ���� �ִϸ��̼� ���� ����.
* 3. FMOD �� ����� ���� ����̽� ����
************************************************************/


