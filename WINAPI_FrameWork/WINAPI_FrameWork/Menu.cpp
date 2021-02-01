#include "Menu.h"
#include "Button.h"
#include "Bitmap.h"
#include "BackGround.h"
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
	m_pButtonList.push_back(ObjectFactroy<Button>::CreateObject(200, (WINSIZEY/2 - 300), "StartButton"));
	//m_pButtonList.push_back(ObjectFactroy<Button>::CreateObject(200, (WINSIZEY/2 - 500), "Option"));
	//m_pButtonList.push_back(ObjectFactroy<Button>::CreateObject(200, (WINSIZEY/2 - 700), "Exit"));

	m_pBackGround = ObjectFactroy<BackGround>::CreateObject(0, 0);


	//** �̹��� ����Ʈ �޾ƿ�
	m_pImageList = BitmapManager::GetInstance()->GetImageList();
}

int Menu::Progress(void)
{
	m_pBackGround->Progress();
	//ObjectManager::GetInstance()->Progress();

	
	for (int i = 0; i < m_pButtonList.size(); i++)
	{
		int iResult = m_pButtonList[i]->Progress();

		if (iResult == 1)
		{
			SceneManager::GetInstance()->SetScene(SCENEID_STAGE);
			return 0;
		}
		else if (iResult == 2)
		{
			return 0;
		}
		else if (iResult == 3)
		{
			DestroyWindow(g_hWnd);
			return 0;
		}
	}
	

	return 0;
}

void Menu::Render(HDC _hdc)
{
	m_pBackGround->Render((*m_pImageList)["Backbuffer"]->GetMemDC());

	//ObjectManager::GetInstance()->Render((*m_pImageList)["Backbuffer"]->GetMemDC());

	for (int i = 0; i < m_pButtonList.size() ; i++)
		m_pButtonList[i]->Render((*m_pImageList)["Backbuffer"]->GetMemDC());

	BitBlt(_hdc,	//** �׸��� �׷� ������
		0,	//** �̹����� ��µ� ������ X
		0,	//** �̹����� ��µ� ������ Y
		WINSIZEX, WINSIZEY,				//** ������ �̹����� ũ�⸸ŭ ����
		(*m_pImageList)["Backbuffer"]->GetMemDC(),	//** ������ �̹���
		0, 0,	// ��� ������ ��ǥ
		SRCCOPY);	// ��� ����
}

void Menu::Release(void)
{
}

