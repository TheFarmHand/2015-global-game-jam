#include "Key.h"
#include "Player.h"
#include <math.h>

LKey::LKey()
{
	SetPosition({ 800, 600 });
	//m_ptStartPosition = { 800, 600 };
	SetSize({ 32, 32 });
	SetRect(SGD::Rectangle({ GetPos(), GetSize() }));
	m_hKey = SGD::GraphicsManager::GetInstance()->LoadTexture("Assets/graphics/Key.png");
}


LKey::~LKey()
{
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hKey);
}


void LKey::Update(float ElapsedTime)
{
}

void LKey::Render()
{
	GraphicsManager::GetInstance()->DrawTexture(m_hKey, GetPos(), 0.0f, { 0.0f, 0.0f }, { 255, 255, 255 }, { 1.0f, 1.0f });
	//GraphicsManager::GetInstance()->DrawRectangle(SGD::Rectangle(GetPos(), GetSize()), { 255, 255, 255, 255 });
}

void LKey::HandleCollision(Object * _object)
{
	if (_object->GetType() == OBJ_Player)
	{
		Player::GetInstance()->SetHasKey(true);
		SetPosition({ -100, -100 });
	}
}