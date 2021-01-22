#include "Stage.h"
#include "Player.h"
#include "Monster.h"
#include "BackGround.h"

#include "Bitmap.h"
#include "ObjectFactroy.h"
#include "ObjectManager.h"
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
	//** 플레이어 생성 후 오브젝트 매니저에 추가
	Object* pPlayer = ObjectFactroy<Player>::CreateObject(WINSIZEX / 2, WINSIZEY / 2);
	ObjectManager::GetInstance()->AddObject(pPlayer->GetKey(), pPlayer);

	//** 백그라운드 생성 후 오브젝트 매니저에 추가
	Object* pBackGround = ObjectFactroy<BackGround>::CreateObject();
	ObjectManager::GetInstance()->AddObject(pBackGround->GetKey(), pBackGround);
	

	



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
	m_pBackBuffer = (new Bitmap)->LoadBmp(L"../Resource/Image/Backbuffer.bmp");


	//** 이미지 리스트
	map<string, Bitmap*>* pImageList = BitmapManager::GetInstance()->GetImageList();

	//** 스테이지 배경 이미지 삽입.
	pImageList->insert(
		make_pair("BackGround", (new Bitmap)->LoadBmp(L"../Resource/Image/BackGround.bmp")));

	//** 플레이어 이미지 삽입
	pImageList->insert(
		make_pair(pPlayer->GetKey(), (new Bitmap)->LoadBmp(L"../Resource/Image/Player.bmp")));
	
	//** 몬스터 이미지 삽입
	pImageList->insert(make_pair("Monster", (new Bitmap)->LoadBmp(L"../Resource/Image/Rect.bmp")));
	
	//** 리스트에 넣어둔 이미지들을 오브젝트 클레스에 보관.
	Object::SetImageList(pImageList);
}

void Stage::Progress(void)
{
	ObjectManager::GetInstance()->Progress();
}


void Stage::Render(HDC _hdc)
{
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

