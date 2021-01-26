#include "MainUpdate.h"
#include "SceneManager.h"
#include "InputManager.h"
#include "SoundManager.h"

#include "Bitmap.h"
#include "BitmapManager.h"

MainUpdate::MainUpdate()
{

}

MainUpdate::~MainUpdate()
{
	Release();
}


void MainUpdate::Initialize(void)
{
	//** �׸��� �׸� DC�� window���� �޾ƿ�.
	m_hdc = GetDC(g_hWnd);

	//** ���콺 ������ �Ⱥ��̰� ����. (true/false)
	//ShowCursor(false);

	//** Ÿ�԰� �ʱ�ȭ. �ѹ��� �����ϸ� ��.
	srand((int)GetTickCount64());

	//** �� �Ŵ��� �ʱ�ȭ. ���� �ΰ�� �����ϰ� ����.
	SceneManager::GetInstance()->SetScene(SCENEID_LOGO);


	//** ���� ����̽� ���� �� �ʱ�ȭ.
	SoundManager::GetInstance()->Initialize();

	//** ���� �߰�
	SoundManager::GetInstance()->AddSound("../Resource/Sound/bleeps.wav", "bleeps");
	SoundManager::GetInstance()->AddSound("../Resource/Sound/horror.wav", "horror");

	//** ���� ��� �� ä�� ����.
	SoundManager::GetInstance()->OnPlaySound("horror", SOUND_CHANNEL_ID_BACKGROUND);
}

void MainUpdate::Progress(void)
{
	//** �� �����Ӹ��� Ű �Է� Ȯ��.
	InputManager::GetInstance()->UpdateKey();

	//** ������� ���尡 ����Ǳ� ������ Ȯ���ϱ� ����.
	SoundManager::GetInstance()->StreamingUpdate();

	SceneManager::GetInstance()->Progress();
}

void MainUpdate::Render(void)
{
	SceneManager::GetInstance()->Render(m_hdc);
}

void MainUpdate::Release(void)
{
	//** window ���� �޾ƿ� �׸����� ������.
	ReleaseDC(g_hWnd, m_hdc);
}


