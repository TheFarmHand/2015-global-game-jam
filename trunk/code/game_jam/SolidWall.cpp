#include "SolidWall.h"
//FOR Testing
#include "Player.h"
#include <math.h>

SolidWall::SolidWall()
{
	//SetSize({ 128, 128 });
	//SetPosition({ 200, 500 });
	SetRect(SGD::Rectangle(GetPos(), GetSize()));
}


SolidWall::~SolidWall()
{
}

void SolidWall::Update(float ElapsedTime)
{
}

void SolidWall::Render()
{
	GraphicsManager::GetInstance()->DrawRectangle(SGD::Rectangle(GetPos(), GetSize()), { 255, 255, 0, 0 });
}