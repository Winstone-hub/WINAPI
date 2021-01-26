#include "Menu.h"
#include "MenuBack.h"
#include "Button.h"
#include "Bitmap.h"
#include "ObjectFactroy.h"
#include "ObjectManager.h"
#include "BitmapManager.h"
#include "SceneManager.h"

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

	//Object* pButton = ObjectFactroy<Button>::CreateObject();
	//ObjectManager::GetInstance()->AddObject(pButton->GetKey(), pButton);

	for (int i = 0; i < 3; i++)
	{
		m_pButton[i] = ObjectFactroy<Button>::CreateObject(200, (WINSIZEY/2 - 300) + (i * 100 + 97));
	}
}

void Menu::Progress(void)
{
	ObjectManager::GetInstance()->Progress();

	for (int i = 0; i < 3; i++)
	{
		int iResult = m_pButton[i]->Progress();

		if (iResult == 1)
		{
			SceneManager::GetInstance()->SetScene(SCENEID_STAGE);
		}
	}
}

void Menu::Render(HDC _hdc)
{
	map<string, Bitmap*>* pBitmapList = BitmapManager::GetInstance()->GetImageList();

	ObjectManager::GetInstance()->Render((*pBitmapList)["BackBuffer"]->GetMemDC());

	for (int i = 0; i < 3; i++)
	{
		m_pButton[i]->Render((*pBitmapList)["BackBuffer"]->GetMemDC());
	}

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

