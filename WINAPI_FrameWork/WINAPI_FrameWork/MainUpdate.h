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
* 1. DC 추가 및 백버퍼 추가. 일괄 출력 제작 예정.
* 2. 폭발 애니메이션 제작 예정.
* 3. FMOD 를 사용한 사운드 디바이스 셋팅
************************************************************/


