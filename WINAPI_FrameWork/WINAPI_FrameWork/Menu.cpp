#include "Menu.h"
#include "MenuBack.h"
#include "Button.h"
#include "Button.h"
#include "Bitmap.h"
#include "ObjectFactroy.h"
#include "ObjectManager.h"
#include "BitmapManager.h"

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::Initialize(void)
{
	Object* pMenuback = ObjectFactroy<MenuBack>::CreateObject();
	ObjectManager::GetInstance()->AddObject(pMenuback->GetKey(), pMenuback);


	Object* pButton = ObjectFactroy<Button>::CreateObject();
	ObjectManager::GetInstance()->AddObject(pButton->GetKey(), pButton);
}

void Menu::Progress(void)
{
	ObjectManager::GetInstance()->Progress();
}

void Menu::Render(HDC _hdc)
{
	ObjectManager::GetInstance()->Render(_hdc);
}

void Menu::Release(void)
{
}

