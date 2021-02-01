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
* 3. 영상처리.
* 4. 폭발 애니메이션 제작 예정.
************************************************************/


//** 리소스 이미지
// https://drive.google.com/drive/folders/16mKYX4u7d3C1gaU8s3E84D_cYPxTclGw?usp=sharing


