#include "Stage.h"
#include "Player.h"
#include "Monster.h"
#include "ObjectFactroy.h"
#include "ObjectManager.h"


Stage::Stage()
{
}

Stage::~Stage()
{
	Release();
}

void Stage::Initialize(void)
{
	/*
	Object* pPlayer = ObjectFactroy<Player>::CreateObject(WINSIZEX / 2, WINSIZEY / 2);

	ObjectManager::GetInstance()->AddObject(pPlayer->GetKey(), pPlayer);

	for (int i = 0; i < 8; i++)
	{
		Object* pMonster = ObjectFactroy<Monster>::CreateObject(
			i * 150 + 100, 100);

		ObjectManager::GetInstance()->AddObject(pMonster->GetKey() , pMonster);
	}
	*/

	m_pObject1 = ObjectFactroy<Player>::CreateObject(WINSIZEX / 2, WINSIZEY / 2);
	m_pObject2 = ObjectFactroy<Monster>::CreateObject(800, 200);
}

void Stage::Progress(void)
{
	m_pObject1->Progress();
	m_pObject2->Progress();

	float fX = m_pObject2->GetPosition().fX - m_pObject1->GetPosition().fX;
	float fY = m_pObject2->GetPosition().fY - m_pObject1->GetPosition().fY;

	float fSum = (m_pObject1->GetScale().fX / 2) + (m_pObject2->GetScale().fX / 2);

	float fLen = sqrt((fX * fX) + (fY * fY));

	if (fSum > fLen)
		m_pObject2->SetScale(0.f, 0.f);

	//ObjectManager::GetInstance()->Progress();
}

void Stage::Render(HDC _hdc)
{
	m_pObject1->Render(_hdc);
	m_pObject2->Render(_hdc);

	//ObjectManager::GetInstance()->Render(_hdc);
}

void Stage::Release(void)
{
	//ObjectManager::GetInstance()->Release();
}

