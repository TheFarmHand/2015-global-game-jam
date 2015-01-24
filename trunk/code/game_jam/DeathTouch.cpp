#include "DeathTouch.h"
//FOR Testign
#include "Player.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

DeathTouch::DeathTouch()
{
	//m_szSize = { 64, 64 };
	//m_ptPosition = { 500, 500 };
	//m_Rect = SGD::Rectangle(m_ptPosition, m_szSize);
}


DeathTouch::~DeathTouch()
{

}

void DeathTouch::Update(float ElapsedTime)
{
}

void DeathTouch::Render()
{
	GraphicsManager::GetInstance()->DrawRectangle(GetRect(), { 255, 255, 0, 0 });
}