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

