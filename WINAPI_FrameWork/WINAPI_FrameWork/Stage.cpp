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
	

	Object* pPlayer = ObjectFactroy<Player>::CreateObject(WINSIZEX / 2, WINSIZEY / 2);

	ObjectManager::GetInstance()->AddObject(pPlayer->GetKey(), pPlayer);

	srand(GetTickCount64());

	for (int i = 0; i < 8; i++)
	{
		Object* pMonster = ObjectFactroy<Monster>::CreateObject(
			rand() % WINSIZEX - 50, rand() % WINSIZEY - 50);

		ObjectManager::GetInstance()->AddObject(pMonster->GetKey() , pMonster);
	}


	map<string, Bitmap*>* m_mapImageList = BitmapManager::GetInstance()->GetImageList();


	m_mapImageList->insert(
		make_pair(pPlayer->GetKey(), (new Bitmap)->LoadBmp(L"../Resource/Player.bmp")));




	Object::SetImageList(m_mapImageList);
}

void Stage::Progress(void)
{
	ObjectManager::GetInstance()->Progress();
}

void Stage::Render(HDC _hdc)
{
	/*
	BitBlt(_hdc,			// ������ ���� �׸��� ?!
		0, 0, 582, 497,		// ������ ���� ���������κ��� ���κб���
		m_Bimmap->GetMemDC(),		// ������ �̹���
		75, 95,				// �������� ����ش�.
		SRCCOPY);			// �ҽ� ������ ��� ������ �����Ѵ�.
	*/

	ObjectManager::GetInstance()->Render(_hdc);
}

void Stage::Release(void)
{
	ObjectManager::GetInstance()->Release();
}

