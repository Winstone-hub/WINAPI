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
	Release();
}


void Logo::Initialize(void)
{
	string strKey = "BackGround_";
	strKey.push_back(48 + (rand() % 4 + 1));

	m_pBackGround[0] = ObjectFactroy<BackGround>::CreateObject(0, 0, strKey);
	m_pBackGround[1] = ObjectFactroy<BackGround>::CreateObject(0, (-WINSIZEY), strKey);

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
	m_pImageList->insert(
		make_pair("Backbuffer", (new Bitmap)->LoadBmp(L"../Resource/Image/Backbuffer.bmp")));





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
	for(int i =  0 ; i < 2 ; i++)
		m_pBackGround[i]->Progress();
	
	ObjectManager::GetInstance()->Progress();

	DWORD dwKey = InputManager::GetInstance()->GetKey();
	if (dwKey & KEY_RETURN || dwKey & KEY_ESCAPE)
		SceneManager::GetInstance()->SetScene(SCENEID_MENU);
	
	return 0;
}

void Logo::Render(HDC _hdc)
{
	for (int i = 0; i < 2; i++)
		m_pBackGround[i]->Render((*m_pImageList)["Backbuffer"]->GetMemDC());

	ObjectManager::GetInstance()->Render((*m_pImageList)["Backbuffer"]->GetMemDC());


	BitBlt(_hdc,	//** �׸��� �׷� ������
		0,	//** �̹����� ��µ� ������ X
		0,	//** �̹����� ��µ� ������ Y
		WINSIZEX, WINSIZEY,				//** ������ �̹����� ũ�⸸ŭ ����
		(*m_pImageList)["Backbuffer"]->GetMemDC(),	//** ������ �̹���
		0, 0,	// ��� ������ ��ǥ
		SRCCOPY);	// ��� ����
}

void Logo::Release(void)
{
	for (int i = 0; i < 2; i++)
	{
		delete m_pBackGround[i];
		m_pBackGround[i] = NULL;
	}
}

