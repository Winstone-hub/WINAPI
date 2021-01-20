#include "MainUpdate.h"
#include "SoundManager.h"

MainUpdate::MainUpdate()
{

}

MainUpdate::~MainUpdate()
{

}


void MainUpdate::Initialize()
{
	SoundManager::GetInStance()->Initialize();
	SoundManager::GetInStance()->AddSound("../Sound/horror.wav", "Horror");
	SoundManager::GetInStance()->AddSound("../Sound/bleeps.wav", "Bleeps");

	SoundManager::GetInStance()->OnPlaySound("Horror", SOUND_CHANNEL_ID_BACKGROUND);
}

void MainUpdate::Progress()
{
	if (GetAsyncKeyState(VK_SPACE))
		SoundManager::GetInStance()->OnPlaySound("Bleeps", SOUND_CHANNEL_ID_EFFECT);

	if (GetAsyncKeyState(VK_RETURN))
		SoundManager::GetInStance()->OnCloseSound(SOUND_CHANNEL_ID_BACKGROUND);

	SoundManager::GetInStance()->StreamingUpdate();
}

void MainUpdate::Render()
{

}

void MainUpdate::Release()
{
	SoundManager::GetInStance()->Release();
}

