#include "Stage.h"
#include "Player.h"
#include "Monster.h"
#include "ObjectFactroy.h"
#include "ObjectManager.h"
#include "Bitmap.h"
#include "BitmapManager.h"


Stage::Stage()
{
}

Stage::~Stage()
{
	Release();
}

void Stage::Initialize(void)
{
	m_iX = 0;



	Object* pPlayer = ObjectFactroy<Player>::CreateObject(WINSIZEX / 2, WINSIZEY / 2);

	ObjectManager::GetInstance()->AddObject(pPlayer->GetKey(), pPlayer);

	srand((int)GetTickCount64());

	/*
	for (int i = 0; i < 8; i++)
	{
		Object* pMonster = ObjectFactroy<Monster>::CreateObject(
			float(rand() % WINSIZEX - 50), 
			float(rand() % WINSIZEY - 50) );

		ObjectManager::GetInstance()->AddObject(pMonster->GetKey() , pMonster);
	}
	*/


	//** BackBuffer 설정
	m_pBackBuffer = (new Bitmap)->LoadBmp(L"../Resource/Backbuffer.bmp");
	m_pBackGround = (new Bitmap)->LoadBmp(L"../Resource/BackGround.bmp");



	//** 이미지 리스트
	map<string, Bitmap*>* pImageList = BitmapManager::GetInstance()->GetImageList();

	//** 플레이어 이미지 삽입
	pImageList->insert(
		make_pair(pPlayer->GetKey(), (new Bitmap)->LoadBmp(L"../Resource/Player.bmp")));
	
	//** 몬스터 이미지 삽입
	pImageList->insert(make_pair("Monster", (new Bitmap)->LoadBmp(L"../Resource/Rect.bmp")));
	
	//** 리스트에 넣어둔 이미지들을 오브젝트 클레스에 보관.
	Object::SetImageList(pImageList);
}

void Stage::Progress(void)
{
	ObjectManager::GetInstance()->Progress();

	m_iX += 10;
	if (m_iX >= 1280)
		m_iX = 0;
}

void Stage::Render(HDC _hdc)
{
	//** 스테이지 이미지를 버퍼에 출력함.
	TransparentBlt(m_pBackBuffer->GetMemDC(),	  // 복사해 넣을 그림판 ?!
		(WINSIZEX / 2) - (1280 / 2),	// 복사할 영역 시작점 X
		(WINSIZEY / 2) - (720 / 2), 	// 복사할 영역 시작점 Y
		1280, 720, 				// 복사할 영역 끝부분 X, Y
		m_pBackGround->GetMemDC(),	// 복사할 이미지 (복사대상)
		0 + m_iX,		// 복사할 시작점 X
		0,			// 복사할 시작점 Y
		1280, 		// 출력할 이미지의 크기 만큼 X
		720,			// 출력할 이미지의 크기 만큼 Y
		RGB(255, 0, 255));		// 해당 색상을 제외



	//** 스테이지 이미지가 출력된 버퍼 위에 오브텍드 이미지를 출력함.
	ObjectManager::GetInstance()->Render(m_pBackBuffer->GetMemDC());

	//** 최종 이미지를 HDC에 출력함.
	BitBlt(_hdc,	//** 그림을 그려 넣을곳
		(WINSIZEX / 2) - (1280 / 2),	//** 이미지가 출력될 시작점 X
		(WINSIZEY / 2) - (720 / 2),	//** 이미지가 출력될 시작점 Y
		1280, 720,				//** 복사할 이미지의 크기만큼 복사
		m_pBackBuffer->GetMemDC(),	//** 복사할 이미지
		0, 0,	// 출력 시작점 좌표
		SRCCOPY);	// 고속 복사
}

void Stage::Release(void)
{
	ObjectManager::GetInstance()->Release();
}

