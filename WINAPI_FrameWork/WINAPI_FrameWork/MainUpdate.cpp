#include "MainUpdate.h"
#include "SceneManager.h"
#include "InputManager.h"

MainUpdate::MainUpdate()
{

}

MainUpdate::~MainUpdate()
{
	Release();
}


void MainUpdate::Initialize(void)
{
	//** �׸��� ����� DC ��� �׸���?! �� ������ �ڵ鿡�� �޾ƿ�.
	m_hdc = GetDC(g_hWnd);

	//** ���콺 �Ⱥ��̰� ����.
	//ShowCursor(false);

	//** ���� �ΰ�� �����ְ� �ʱ�ȭ ������ ��������ش�.
	SceneManager::GetInstance()->SetScene(SCENEID_LOGO);
}

void MainUpdate::Progress(void)
{
	//** Ű �Է��� Ȯ�� �Ѵ�.
	InputManager::GetInstance()->UpdateKey();



	/**********************************************************
	* SceneManager::GetInstance()->Progress()
	* 
	* �ʿ��� ������� ����
	* Progress() ���ο����� �÷��̾��� �̵� �� ���� Ȥ�� 
	* ���� ���� �� ���Ϳ��� �浹 �� ���� ������� ���� �ȴ�.
	***********************************************************/
	SceneManager::GetInstance()->Progress();
}

void MainUpdate::Render(void)
{
	//** �� �Ŵ��� 
	SceneManager::GetInstance()->Render(m_hdc);
}

void MainUpdate::Release(void)
{
	//** Ŭ������ ���������� ������ ���Ŵ����� ����� �����Ѵ�.
	SceneManager::GetInstance()->Release();
}


