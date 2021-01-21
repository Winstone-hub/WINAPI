#include "Stage.h"
#include "Player.h"
#include "Monster.h"
#include "ObjectFactroy.h"
#include "ObjectManager.h"
#include "Bitmap.h"
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
	m_iX = 0;



	Object* pPlayer = ObjectFactroy<Player>::CreateObject(WINSIZEX / 2, WINSIZEY / 2);

	ObjectManager::GetInstance()->AddObject(pPlayer->GetKey(), pPlayer);

	srand((int)GetTickCount64());

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
	m_pBackBuffer = (new Bitmap)->LoadBmp(L"../Resource/Backbuffer.bmp");
	m_pBackGround = (new Bitmap)->LoadBmp(L"../Resource/BackGround.bmp");



	//** �̹��� ����Ʈ
	map<string, Bitmap*>* pImageList = BitmapManager::GetInstance()->GetImageList();

	//** �÷��̾� �̹��� ����
	pImageList->insert(
		make_pair(pPlayer->GetKey(), (new Bitmap)->LoadBmp(L"../Resource/Player.bmp")));
	
	//** ���� �̹��� ����
	pImageList->insert(make_pair("Monster", (new Bitmap)->LoadBmp(L"../Resource/Rect.bmp")));
	
	//** ����Ʈ�� �־�� �̹������� ������Ʈ Ŭ������ ����.
	Object::SetImageList(pImageList);
}

void Stage::Progress(void)
{
	ObjectManager::GetInstance()->Progress();

	m_iX += 10;
	if (m_iX >= 1280)
		m_iX = 0;
}

void Stage::Render(HDC _hdc)
{
	//** �������� �̹����� ���ۿ� �����.
	TransparentBlt(m_pBackBuffer->GetMemDC(),	  // ������ ���� �׸��� ?!
		(WINSIZEX / 2) - (1280 / 2),	// ������ ���� ������ X
		(WINSIZEY / 2) - (720 / 2), 	// ������ ���� ������ Y
		1280, 720, 				// ������ ���� ���κ� X, Y
		m_pBackGround->GetMemDC(),	// ������ �̹��� (������)
		0 + m_iX,		// ������ ������ X
		0,			// ������ ������ Y
		1280, 		// ����� �̹����� ũ�� ��ŭ X
		720,			// ����� �̹����� ũ�� ��ŭ Y
		RGB(255, 0, 255));		// �ش� ������ ����



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

