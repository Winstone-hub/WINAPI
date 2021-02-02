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
	/*********************************
	   **  Menu image is insert. **
	**********************************/

	//** Background ��׶��� �̹��� ����
	for (int i = 1; i < 5; i++)
	{
		TCHAR pBuffer[128];

		wsprintf(pBuffer, TEXT("../Resource/Image/Common/Background/%02d.bmp"), i);

		//MessageBox(g_hWnd, pBuffer, L"", NULL);

		string str = "BackGround_";
		str.push_back(48 + i);

		m_ImageList[str] = (new Bitmap)->LoadBmp(pBuffer);
	}

	//** ���� �̹��� ����. (�̹����� �ѹ��� ����ϱ� ���� �׸��� �뵵)
	m_ImageList["Backbuffer"] = (new Bitmap)->LoadBmp(L"../Resource/Image/Common/Backbuffer.bmp");






	/*********************************
	   **  Menu image is insert. **
	**********************************/

	//** ���� �̹��� ����. (�̹����� �ѹ��� ����ϱ� ���� �׸��� �뵵)
	m_ImageList["StartButton"] = (new Bitmap)->LoadBmp(L"../Resource/Image/Menu/btn_purchase_n-horz.bmp");





	m_pButtonList.push_back(ObjectFactroy<Button>::CreateObject(200, (WINSIZEY/2 - 300), "StartButton"));
	//m_pButtonList.push_back(ObjectFactroy<Button>::CreateObject(200, (WINSIZEY/2 - 500), "Option"));
	//m_pButtonList.push_back(ObjectFactroy<Button>::CreateObject(200, (WINSIZEY/2 - 700), "Exit"));

	m_pBackGround = ObjectFactroy<BackGround>::CreateObject(0, 0);


	Object::SetImageList(&m_ImageList);
}

int Menu::Progress(void)
{
	m_pBackGround->Progress();

	
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
	m_pBackGround->Render(m_ImageList["Backbuffer"]->GetMemDC());


	for (int i = 0; i < m_pButtonList.size() ; i++)
		m_pButtonList[i]->Render(m_ImageList["Backbuffer"]->GetMemDC());

	BitBlt(_hdc,	//** �׸��� �׷� ������
		0,	//** �̹����� ��µ� ������ X
		0,	//** �̹����� ��µ� ������ Y
		WINSIZEX, WINSIZEY,				//** ������ �̹����� ũ�⸸ŭ ����
		m_ImageList["Backbuffer"]->GetMemDC(),	//** ������ �̹���
		0, 0,	// ��� ������ ��ǥ
		SRCCOPY);	// ��� ����
}

void Menu::Release(void)
{
}

