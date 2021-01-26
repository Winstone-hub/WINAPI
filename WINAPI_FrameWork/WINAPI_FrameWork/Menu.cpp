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


	BitBlt(_hdc,	//** �׸��� �׷� ������
		(WINSIZEX / 2) - (1280 / 2),	//** �̹����� ��µ� ������ X
		(WINSIZEY / 2) - (720 / 2),	//** �̹����� ��µ� ������ Y
		1280, 720,				//** ������ �̹����� ũ�⸸ŭ ����
		(*pBitmapList)["BackBuffer"]->GetMemDC(),	//** ������ �̹���
		0, 0,	// ��� ������ ��ǥ
		SRCCOPY);	// ��� ����
}

void Menu::Release(void)
{
}

