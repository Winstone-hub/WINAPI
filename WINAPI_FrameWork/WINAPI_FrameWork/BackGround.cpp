#include "BackGround.h"


BackGround::BackGround()
{

}

BackGround::~BackGround()
{

}


void BackGround::Initialize(void)
{
	m_tTransPos.Position = Vector3(0, 0);
	m_tTransPos.Rotation = Vector3(0.f, 0.f, 0.f);
	m_tTransPos.Scale = Vector3(768, 1024);

	m_fAngle = 0.f;
	m_fSpeed = 5.f;
	m_strKey = "BackGround_1";
	/*			   
	m_strKey.push_back(48 + (rand() % 4 + 1));
	*/
}

int BackGround::Progress(void)
{
	m_tTransPos.Position.fY += m_fSpeed;


	if (m_tTransPos.Position.fY >= WINSIZEY)
		m_tTransPos.Position.fY = (-WINSIZEY);


	return 0;
}

void BackGround::Render(HDC _hdc)
{
	//** Menu 백그라운드 이미지를 버퍼에 출력함.
	TransparentBlt(_hdc,	  // 복사해 넣을 그림판 ?!
		m_tTransPos.Position.fX,	// 복사할 영역 시작점 X
		m_tTransPos.Position.fY, 	// 복사할 영역 시작점 Y
		m_tTransPos.Position.fX + m_tTransPos.Scale.fX,	// 복사할 영역 끝부분 X
		/*m_tTransPos.Position.fY + */m_tTransPos.Scale.fY, // 복사할 영역 끝부분 Y
		(*m_ImageList)[m_strKey]->GetMemDC(),	// 복사할 이미지 (복사대상)
		(int)0 * m_tTransPos.Scale.fX,		// 복사할 시작점 X
		(int)0 * m_tTransPos.Scale.fY,		// 복사할 시작점 Y
		(int)m_tTransPos.Scale.fX, 		// 출력할 이미지의 크기 만큼 X
		(int)m_tTransPos.Scale.fY,		// 출력할 이미지의 크기 만큼 Y
		RGB(255, 0, 255));		// 해당 색상을 제외
}


void BackGround::Release(void)
{

}
