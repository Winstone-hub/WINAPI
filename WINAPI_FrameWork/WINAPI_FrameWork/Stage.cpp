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
	//** �÷��̾� ���� �� ������Ʈ �Ŵ����� �߰�
	Object* pPlayer = ObjectFactroy<Player>::CreateObject(WINSIZEX / 2, WINSIZEY / 2);
	ObjectManager::GetInstance()->AddObject(pPlayer->GetKey(), pPlayer);

	//** ��׶��� ���� �� ������Ʈ �Ŵ����� �߰�
	Object* pBackGround = ObjectFactroy<BackGround>::CreateObject();
	ObjectManager::GetInstance()->AddObject(pBackGround->GetKey(), pBackGround);
	

	



	/*
	for (int i = 0; i < 8; i++)
	{
		Object* pMonster = ObjectFactroy<Monster>::CreateObject(
			float(rand() % WINSIZEX - 50), 
			float(rand() % WINSIZEY - 50) );

		ObjectManager::GetInstance()->AddObject(pMonster->GetKey() , pMonster);
	}
	*/

	//** BackBuffer ����
	m_pBackBuffer = (new Bitmap)->LoadBmp(L"../Resource/Image/Backbuffer.bmp");


	//** �̹��� ����Ʈ
	map<string, Bitmap*>* pImageList = BitmapManager::GetInstance()->GetImageList();

	//** �������� ��� �̹��� ����.
	pImageList->insert(
		make_pair("BackGround", (new Bitmap)->LoadBmp(L"../Resource/Image/BackGround.bmp")));

	//** �÷��̾� �̹��� ����
	pImageList->insert(
		make_pair(pPlayer->GetKey(), (new Bitmap)->LoadBmp(L"../Resource/Image/Player.bmp")));
	
	//** ���� �̹��� ����
	pImageList->insert(make_pair("Monster", (new Bitmap)->LoadBmp(L"../Resource/Image/Rect.bmp")));
	
	//** ����Ʈ�� �־�� �̹������� ������Ʈ Ŭ������ ����.
	Object::SetImageList(pImageList);
}

void Stage::Progress(void)
{
	ObjectManager::GetInstance()->Progress();
}


void Stage::Render(HDC _hdc)
{
	//** �������� �̹����� ��µ� ���� ���� �����ص� �̹����� �����.
	ObjectManager::GetInstance()->Render(m_pBackBuffer->GetMemDC());

	//** ���� �̹����� HDC�� �����.
	BitBlt(_hdc,	//** �׸��� �׷� ������
		(WINSIZEX / 2) - (1280 / 2),	//** �̹����� ��µ� ������ X
		(WINSIZEY / 2) - (720 / 2),	//** �̹����� ��µ� ������ Y
		1280, 720,				//** ������ �̹����� ũ�⸸ŭ ����
		m_pBackBuffer->GetMemDC(),	//** ������ �̹���
		0, 0,	// ��� ������ ��ǥ
		SRCCOPY);	// ��� ����
}

void Stage::Release(void)
{
	ObjectManager::GetInstance()->Release();
}

