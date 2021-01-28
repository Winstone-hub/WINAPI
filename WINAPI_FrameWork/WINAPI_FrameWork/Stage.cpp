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
	/*********************************
	   **  Stage image is insert. **
	**********************************/

	//** 스테이지 배경 이미지 삽입.
	(*m_pImageList)["BackGround"] = (new Bitmap)->LoadBmp(L"../Resource/Image/BackGround.bmp");

	//** 플레이어 이미지 삽입
	(*m_pImageList)["Player"] = (new Bitmap)->LoadBmp(L"../Resource/Image/Player.bmp");

	//** 몬스터 이미지 삽입
	m_pImageList->insert(make_pair("Monster", (new Bitmap)->LoadBmp(L"../Resource/Image/Rect.bmp")));


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
	Object::SetImageList(m_pImageList);
}

int Stage::Progress(void)
{
	ObjectManager::GetInstance()->Progress();

	return 0;
}


void Stage::Render(HDC _hdc)
{
	map<string, Bitmap*>* pBitmapList = BitmapManager::GetInstance()->GetImageList();

	//** 스테이지 이미지가 출력된 버퍼 위에 오브텍드 이미지를 출력함.
	ObjectManager::GetInstance()->Render((*pBitmapList)["BackBuffer"]->GetMemDC());

	//** 최종 이미지를 HDC에 출력함.
	BitBlt(_hdc,	//** 그림을 그려 넣을곳
		0,	//** 이미지가 출력될 시작점 X
		0,	//** 이미지가 출력될 시작점 Y
		WINSIZEX, WINSIZEY,				//** 복사할 이미지의 크기만큼 복사
		(*pBitmapList)["BackBuffer"]->GetMemDC(),	//** 복사할 이미지
		0, 0,	// 출력 시작점 좌표
		SRCCOPY);	// 고속 복사
}

void Stage::Release(void)
{
	ObjectManager::GetInstance()->Release();
}

