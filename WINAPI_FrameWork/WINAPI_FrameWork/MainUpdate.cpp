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
	m_hdc = GetDC(g_hWnd);

	//ShowCursor(false);

	SceneManager::GetInstance()->SetScene(SCENEID_LOGO);
}

void MainUpdate::Progress(void)
{
	InputManager::GetInstance()->UpdateKey();

	SceneManager::GetInstance()->Progress();
}

void MainUpdate::Render(void)
{
	Rectangle(m_hdc, 0, 0, WINSIZEX, WINSIZEY);

	SceneManager::GetInstance()->Render(m_hdc);
}

void MainUpdate::Release(void)
{

}


