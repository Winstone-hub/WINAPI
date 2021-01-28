#include "Logo.h"
#include "MenuBack.h"
#include "Button.h"
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
	//** �̹��� ����Ʈ
	m_pImageList = BitmapManager::GetInstance()->GetImageList();


	Object* pMenuback = ObjectFactroy<MenuBack>::CreateObject();
	ObjectManager::GetInstance()->AddObject(pMenuback->GetKey(), pMenuback);

	m_pButtonList.push_back(ObjectFactroy<Button>::CreateObject("LogoButton", WINSIZEX / 2, (WINSIZEY / 2) - 300));


	/*********************************
	   **  Logo image is insert. **
	**********************************/

	//** Menu ��׶��� �̹��� ����
	for (int i = 1 ; i < 5 ; i++ )
	{
		TCHAR pBuffer[128];

		wsprintf(pBuffer, TEXT("../Resource/Image/Background/%02d.bmp"),i);

		//MessageBox(g_hWnd, pBuffer, L"", NULL);
		
		string str = "BackGround_";
		str.push_back(48 + i);

		m_pImageList->insert(make_pair(str, (new Bitmap)->LoadBmp(pBuffer)));
	}


	//** Menu Button �̹��� ����
	m_pImageList->insert(
		make_pair("Logo", (new Bitmap)->LoadBmp(L"../Resource/Image/Menu/logo.bmp")));


	//** ���� �̹��� ����. (�̹����� �ѹ��� ����ϱ� ���� �׸��� �뵵)
	m_pImageList->insert(
		make_pair("BackBuffer", (new Bitmap)->LoadBmp(L"../Resource/Image/Backbuffer.bmp")));



	//** ����Ʈ�� �־�� �̹������� ������Ʈ Ŭ������ ����.
	Object::SetImageList(m_pImageList);
}

int Logo::Progress(void)
{
	ObjectManager::GetInstance()->Progress();


	DWORD dwKey = InputManager::GetInstance()->GetKey();

	if (dwKey & KEY_RETURN || dwKey & KEY_ESCAPE)
		SceneManager::GetInstance()->SetScene(SCENEID_MENU);

		return 0;
}

void Logo::Render(HDC _hdc)
{
	ObjectManager::GetInstance()->Render(_hdc);
}

void Logo::Release(void)
{
}

