#include "Logo.h"
#include "Button.h"
#include "LogoObject.h"
#include "BackGround.h"
#include"InputManager.h"
#include "SceneManager.h"

#include "Bitmap.h"
#include "ObjectFactroy.h"
#include "ObjectManager.h"
#include "BitmapManager.h"
#include "SoundManager.h"


Logo::Logo()
{

}

Logo::~Logo()
{

}


void Logo::Initialize(void)
{
	Object* pBackGround = ObjectFactroy<BackGround>::CreateObject();
	ObjectManager::GetInstance()->AddObject(pBackGround->GetKey(), pBackGround);

	Object* pLogoObject = ObjectFactroy<LogoObject>::CreateObject(WINSIZEX / 2, 300, "Logo");
	ObjectManager::GetInstance()->AddObject(pLogoObject->GetKey(), pLogoObject);





	/*********************************
	   **  Logo image is insert. **
	**********************************/

	//** �̹��� ����Ʈ �޾ƿ�
	m_pImageList = BitmapManager::GetInstance()->GetImageList();


	//** Background ��׶��� �̹��� ����
	for (int i = 1 ; i < 5 ; i++ )
	{
		TCHAR pBuffer[128];

		wsprintf(pBuffer, TEXT("../Resource/Image/Common/Background/%02d.bmp"),i);

		//MessageBox(g_hWnd, pBuffer, L"", NULL);
		
		string str = "BackGround_";
		str.push_back(48 + i);

		m_pImageList->insert(make_pair(str, (new Bitmap)->LoadBmp(pBuffer)));
	}


	//** Logo �̹��� ����
	m_pImageList->insert(
		make_pair("Logo", (new Bitmap)->LoadBmp(L"../Resource/Image/Logo/logo.bmp")));

	//** ���� �̹��� ����. (�̹����� �ѹ��� ����ϱ� ���� �׸��� �뵵)
	m_pBackBuffer = (new Bitmap)->LoadBmp(L"../Resource/Image/Backbuffer.bmp");

	m_pImageList->insert(
		make_pair("BackBuffer", m_pBackBuffer));



	/*********************************
	   **  Menu image is insert. **
	**********************************/

	//** ���� �̹��� ����. (�̹����� �ѹ��� ����ϱ� ���� �׸��� �뵵)
	m_pImageList->insert(
		make_pair("StartButton", (new Bitmap)->LoadBmp(L"../Resource/Image/Menu/btn_purchase_n-horz.bmp")));



	//** ����Ʈ�� �־�� �̹������� ������Ʈ Ŭ������ ����.
	Object::SetImageList(m_pImageList);







	//** ���� ��� �� ä�� ����.
	SoundManager::GetInstance()->OnPlaySound("Logo", SOUND_CHANNEL_ID_LOGO);
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
	ObjectManager::GetInstance()->Render(m_pBackBuffer->GetMemDC());
}

void Logo::Release(void)
{
}

