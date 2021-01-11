#include "Logo.h"
#include"InputManager.h"
#include "SceneManager.h"

Logo::Logo()
{

}

Logo::~Logo()
{

}


void Logo::Initialize(void)
{

}

void Logo::Progress(void)
{
	DWORD dwKey = InputManager::GetInstance()->GetKey();

	if (dwKey & KEY_RETURN)
		SceneManager::GetInstance()->SetScene(SCENEID_STAGE);
}

void Logo::Render(HDC _hdc)
{
	Rectangle(_hdc,
		int(100 - (100 / 2)),
		int(100 - (100 / 2)), 
		int(100 + (100 / 2)),
		int(100 + (100 / 2)) );
}

void Logo::Release(void)
{
}

