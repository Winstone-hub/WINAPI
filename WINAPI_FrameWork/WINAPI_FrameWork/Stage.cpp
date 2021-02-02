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

	//** Background 백그라운드 이미지 삽입
	for (int i = 1; i < 5; i++)
	{
		TCHAR pBuffer[128];

		wsprintf(pBuffer, TEXT("../Resource/Image/Common/Background/%02d.bmp"), i);

		string str = "BackGround_";
		str.push_back(48 + i);

		m_ImageList[str] = (new Bitmap)->LoadBmp(pBuffer);
	}

	//** 버퍼 이미지 삽입. (이미지를 한번에 출력하기 위한 그림판 용도)
	m_ImageList["Backbuffer"] = (new Bitmap)->LoadBmp(L"../Resource/Image/Common/Backbuffer.bmp");

	//** 플레이어 이미지 삽입
	m_ImageList["Player"] = (new Bitmap)->LoadBmp(L"../Resource/Image/Stage/Player.bmp");

	//** 몬스터 이미지 삽입
	m_ImageList["Monster"] = (new Bitmap)->LoadBmp(L"../Resource/Image/Stage/Rect.bmp");




	//** 플레이어 생성 후 오브젝트 매니저에 추가
	Object* pPlayer = ObjectFactroy<Player>::CreateObject(WINSIZEX / 2, WINSIZEY / 2);
	ObjectManager::GetInstance()->AddObject(pPlayer->GetKey(), pPlayer);

	//** 백그라운드 생성 후 오브젝트 매니저에 추가
	//Object* pBackGround = ObjectFactroy<BackGround>::CreateObject();
	//ObjectManager::GetInstance()->AddObject(pBackGround->GetKey(), pBackGround);
	
	
	for (int i = 0; i < 8; i++)
	{
		Object* pMonster = ObjectFactroy<Monster>::CreateObject(
			float(rand() % WINSIZEX - 50), 
			float(rand() % WINSIZEY - 50) );

		ObjectManager::GetInstance()->AddObject(pMonster->GetKey() , pMonster);
	}
	
	Object::SetImageList(&m_ImageList);
}

int Stage::Progress(void)
{
	ObjectManager::GetInstance()->Progress();

	return 0;
}


void Stage::Render(HDC _hdc)
{
	//** 스테이지 이미지가 출력된 버퍼 위에 오브텍드 이미지를 출력함.
	ObjectManager::GetInstance()->Render( m_ImageList["Backbuffer"]->GetMemDC() );

	//** 최종 이미지를 HDC에 출력함.
	BitBlt(_hdc,	//** 그림을 그려 넣을곳
		0,	//** 이미지가 출력될 시작점 X
		0,	//** 이미지가 출력될 시작점 Y
		WINSIZEX, WINSIZEY,				//** 복사할 이미지의 크기만큼 복사
		m_ImageList["Backbuffer"]->GetMemDC(),	//** 복사할 이미지
		0, 0,	// 출력 시작점 좌표
		SRCCOPY);	// 고속 복사
}

void Stage::Release(void)
{
	ObjectManager::GetInstance()->Release();
}

