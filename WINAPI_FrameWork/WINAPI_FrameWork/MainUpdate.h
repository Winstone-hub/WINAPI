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
* 1. Stage ���� �ذ�
* 2. Alpha Image  .
* 3. ����ó��.
* 4. ���� �ִϸ��̼� ���� ����.
************************************************************/


