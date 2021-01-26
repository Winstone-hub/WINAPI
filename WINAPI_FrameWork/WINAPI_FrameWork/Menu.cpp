#include "Menu.h"
#include "MenuBack.h"
#include "Button.h"
#include "Button.h"
#include "Bitmap.h"
#include "ObjectFactroy.h"
#include "ObjectManager.h"
#include "BitmapManager.h"

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::Initialize(void)
{
	Object* pMenuback = ObjectFactroy<MenuBack>::CreateObject();
	ObjectManager::GetInstance()->AddObject(pMenuback->GetKey(), pMenuback);
//
//
	Object* pButton = ObjectFactroy<Button>::CreateObject();
	ObjectManager::GetInstance()->AddObject(pButton->GetKey(), pButton);
}

void Menu::Progress(void)
{
	ObjectManager::GetInstance()->Progress();
}

void Menu::Render(HDC _hdc)
{
	map<string, Bitmap*>* pBitmapList = BitmapManager::GetInstance()->GetImageList();

	ObjectManager::GetInstance()->Render((*pBitmapList)["BackBuffer"]->GetMemDC());


	BitBlt(_hdc,	//** 그림을 그려 넣을곳
		(WINSIZEX / 2) - (1280 / 2),	//** 이미지가 출력될 시작점 X
		(WINSIZEY / 2) - (720 / 2),	//** 이미지가 출력될 시작점 Y
		1280, 720,				//** 복사할 이미지의 크기만큼 복사
		(*pBitmapList)["BackBuffer"]->GetMemDC(),	//** 복사할 이미지
		0, 0,	// 출력 시작점 좌표
		SRCCOPY);	// 고속 복사
}

void Menu::Release(void)
{
}

