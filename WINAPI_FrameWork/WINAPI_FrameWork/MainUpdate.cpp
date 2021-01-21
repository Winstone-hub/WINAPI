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
	//** 그림을 출력할 DC 라는 그림판?! 을 윈도우 핸들에서 받아옴.
	m_hdc = GetDC(g_hWnd);

	//** 마우스 안보이게 해줌.
	//ShowCursor(false);

	//** 씬을 로고로 정해주고 초기화 구문을 실행시켜준다.
	SceneManager::GetInstance()->SetScene(SCENEID_LOGO);
}

void MainUpdate::Progress(void)
{
	//** 키 입력을 확인 한다.
	InputManager::GetInstance()->UpdateKey();



	/**********************************************************
	* SceneManager::GetInstance()->Progress()
	* 
	* 필요한 연산들을 진행
	* Progress() 내부에서는 플레이어의 이동 및 공격 혹은 
	* 블렛의 방향 및 몬스터와의 충돌 등 많은 연산들이 진행 된다.
	***********************************************************/
	SceneManager::GetInstance()->Progress();
}

void MainUpdate::Render(void)
{
	//** 씬 매니저 
	SceneManager::GetInstance()->Render(m_hdc);
}

void MainUpdate::Release(void)
{
	//** 클레스를 빠저나오기 직전에 씬매니져의 릴리즈를 실행한다.
	SceneManager::GetInstance()->Release();
}


