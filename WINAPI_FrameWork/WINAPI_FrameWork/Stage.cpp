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

	//** �������� ��� �̹��� ����.
	(*m_pImageList)["BackGround"] = (new Bitmap)->LoadBmp(L"../Resource/Image/BackGround.bmp");

	//** �÷��̾� �̹��� ����
	(*m_pImageList)["Player"] = (new Bitmap)->LoadBmp(L"../Resource/Image/Player.bmp");

	//** ���� �̹��� ����
	m_pImageList->insert(make_pair("Monster", (new Bitmap)->LoadBmp(L"../Resource/Image/Rect.bmp")));


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
	Object::SetImageList(m_pImageList);
}

int Stage::Progress(void)
{
	ObjectManager::GetInstance()->Progress();

	return 0;
}


void Stage::Render(HDC _hdc)
{
	map<string, Bitmap*>* pBitmapList = BitmapManager::GetInstance()->GetImageList();

	//** �������� �̹����� ��µ� ���� ���� �����ص� �̹����� �����.
	ObjectManager::GetInstance()->Render((*pBitmapList)["BackBuffer"]->GetMemDC());

	//** ���� �̹����� HDC�� �����.
	BitBlt(_hdc,	//** �׸��� �׷� ������
		0,	//** �̹����� ��µ� ������ X
		0,	//** �̹����� ��µ� ������ Y
		WINSIZEX, WINSIZEY,				//** ������ �̹����� ũ�⸸ŭ ����
		(*pBitmapList)["BackBuffer"]->GetMemDC(),	//** ������ �̹���
		0, 0,	// ��� ������ ��ǥ
		SRCCOPY);	// ��� ����
}

void Stage::Release(void)
{
	ObjectManager::GetInstance()->Release();
}

