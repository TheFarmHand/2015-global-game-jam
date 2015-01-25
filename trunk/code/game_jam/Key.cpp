#include "Key.h"
#include "Player.h"
#include <math.h>

LKey::LKey()
{
	SetPosition({ 800, 600 });
	//m_ptStartPosition = { 800, 600 };
	SetSize({ 32, 32 });
	SetRect(SGD::Rectangle({ GetPos(), GetSize() }));
}


LKey::~LKey()
{
}


void LKey::Update(float ElapsedTime)
{
}

void LKey::Render()
{
	GraphicsManager::GetInstance()->DrawRectangle(SGD::Rectangle(GetPos(), GetSize()), { 255, 255, 255, 255 });
}

void LKey::HandleCollision(Object * _object)
{
	if (_object->GetType() == OBJ_Player)
	{
		Player::GetInstance()->SetHasKey(true);
		SetPosition({ -100, -100 });
	}
}