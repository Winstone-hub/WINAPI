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


	
}

void Stage::Progress(void)
{
	ObjectManager::GetInstance()->Progress();
}


void Stage::Render(HDC _hdc)
{
	//** �������� �̹����� ��µ� ���� ���� �����ص� �̹����� �����.
	ObjectManager::GetInstance()->Render(_hdc);


	/*
	//** ���� �̹����� HDC�� �����.
	BitBlt(_hdc,	//** �׸��� �׷� ������
		(WINSIZEX / 2) - (1280 / 2),	//** �̹����� ��µ� ������ X
		(WINSIZEY / 2) - (720 / 2),	//** �̹����� ��µ� ������ Y
		1280, 720,				//** ������ �̹����� ũ�⸸ŭ ����
		m_pBackBuffer->GetMemDC(),	//** ������ �̹���
		0, 0,	// ��� ������ ��ǥ
		SRCCOPY);	// ��� ����
	*/
}

void Stage::Release(void)
{
	ObjectManager::GetInstance()->Release();
}

