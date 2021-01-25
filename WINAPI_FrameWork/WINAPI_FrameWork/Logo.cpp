#include "Logo.h"
#include"InputManager.h"
#include "SceneManager.h"

#include "Bitmap.h"
#include "ObjectFactroy.h"
#include "ObjectManager.h"
#include "BitmapManager.h"


Logo::Logo()
{

}

Logo::~Logo()
{

}


void Logo::Initialize(void)
{
	//** 이미지 리스트
	m_pImageList = BitmapManager::GetInstance()->GetImageList();




	/*********************************
	   **  Menu image is insert. **
	**********************************/

	//** Menu 백그라운드 이미지 삽입
	m_pImageList->insert(
		make_pair("MenuBack", (new Bitmap)->LoadBmp(L"../Resource/Image/Menu/MenuBack.bmp")));


	//** Menu Button 이미지 삽입
	m_pImageList->insert(
		make_pair("PlayButton", (new Bitmap)->LoadBmp(L"../Resource/Image/Menu/PlayButton.bmp")));







	/*********************************
	   **  Stage image is insert. **
	**********************************/

	//** 스테이지 배경 이미지 삽입.
	m_pImageList->insert(
		make_pair("BackGround", (new Bitmap)->LoadBmp(L"../Resource/Image/BackGround.bmp")));

	//** 플레이어 이미지 삽입
	m_pImageList->insert(
		make_pair("Player", (new Bitmap)->LoadBmp(L"../Resource/Image/Player.bmp")));

	//** 몬스터 이미지 삽입
	m_pImageList->insert(make_pair("Monster", (new Bitmap)->LoadBmp(L"../Resource/Image/Rect.bmp")));



	//** 리스트에 넣어둔 이미지들을 오브젝트 클레스에 보관.
	Object::SetImageList(m_pImageList);
}

void Logo::Progress(void)
{
	DWORD dwKey = InputManager::GetInstance()->GetKey();

	if (dwKey & KEY_RETURN /*|| dwKey & KEY_ESCAPE*/)
		SceneManager::GetInstance()->SetScene(SCENEID_MENU);
}

void Logo::Render(HDC _hdc)
{
	Rectangle(_hdc,
		int(100 - (100 / 2)),
		int(100 - (100 / 2)), 
		int(100 + (100 / 2)),
		int(100 + (100 / 2)) );
}

void Logo::Release(void)
{
}

