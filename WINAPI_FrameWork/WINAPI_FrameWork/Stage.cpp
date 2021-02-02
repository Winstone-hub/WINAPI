#include "Stage.h"
#include "Player.h"
#include "Monster.h"
#include "BackGround.h"

#include "Bitmap.h"
#include "ObjectFactroy.h"
#include "ObjectManager.h"
#include "BitmapManager.h"


Stage::Stage()
{
}

Stage::~Stage()
{
	Release();
}

void Stage::Initialize(void)
{
	/*********************************
	   **  Stage image is insert. **
	**********************************/

	//** Background ��׶��� �̹��� ����
	for (int i = 1; i < 5; i++)
	{
		TCHAR pBuffer[128];

		wsprintf(pBuffer, TEXT("../Resource/Image/Common/Background/%02d.bmp"), i);

		string str = "BackGround_";
		str.push_back(48 + i);

		m_ImageList[str] = (new Bitmap)->LoadBmp(pBuffer);
	}

	//** ���� �̹��� ����. (�̹����� �ѹ��� ����ϱ� ���� �׸��� �뵵)
	m_ImageList["Backbuffer"] = (new Bitmap)->LoadBmp(L"../Resource/Image/Common/Backbuffer.bmp");

	//** �÷��̾� �̹��� ����
	m_ImageList["Player"] = (new Bitmap)->LoadBmp(L"../Resource/Image/Stage/Player.bmp");

	//** ���� �̹��� ����
	m_ImageList["Monster"] = (new Bitmap)->LoadBmp(L"../Resource/Image/Stage/Rect.bmp");




	//** �÷��̾� ���� �� ������Ʈ �Ŵ����� �߰�
	Object* pPlayer = ObjectFactroy<Player>::CreateObject(WINSIZEX / 2, WINSIZEY / 2);
	ObjectManager::GetInstance()->AddObject(pPlayer->GetKey(), pPlayer);

	//** ��׶��� ���� �� ������Ʈ �Ŵ����� �߰�
	//Object* pBackGround = ObjectFactroy<BackGround>::CreateObject();
	//ObjectManager::GetInstance()->AddObject(pBackGround->GetKey(), pBackGround);
	
	
	for (int i = 0; i < 8; i++)
	{
		Object* pMonster = ObjectFactroy<Monster>::CreateObject(
			float(rand() % WINSIZEX - 50), 
			float(rand() % WINSIZEY - 50) );

		ObjectManager::GetInstance()->AddObject(pMonster->GetKey() , pMonster);
	}
	
	Object::SetImageList(&m_ImageList);
}

int Stage::Progress(void)
{
	ObjectManager::GetInstance()->Progress();

	return 0;
}


void Stage::Render(HDC _hdc)
{
	//** �������� �̹����� ��µ� ���� ���� �����ص� �̹����� �����.
	ObjectManager::GetInstance()->Render( m_ImageList["Backbuffer"]->GetMemDC() );

	//** ���� �̹����� HDC�� �����.
	BitBlt(_hdc,	//** �׸��� �׷� ������
		0,	//** �̹����� ��µ� ������ X
		0,	//** �̹����� ��µ� ������ Y
		WINSIZEX, WINSIZEY,				//** ������ �̹����� ũ�⸸ŭ ����
		m_ImageList["Backbuffer"]->GetMemDC(),	//** ������ �̹���
		0, 0,	// ��� ������ ��ǥ
		SRCCOPY);	// ��� ����
}

void Stage::Release(void)
{
	ObjectManager::GetInstance()->Release();
}

