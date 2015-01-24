#include "Key.h"
#include "Player.h"
#include <math.h>

LKey::LKey()
{
	SetPosition({ 800, 600 });
	SetSize({ 32, 32 });
	SetRect(SGD::Rectangle({ GetPos(), GetSize() }));
}


LKey::~LKey()
{
}


void LKey::Update(float ElapsedTime)
{
	SGD::Rectangle wallRect = GetRect();
	SGD::Rectangle otherRect = Player::GetInstance()->GetRect();

	if (!wallRect.IsIntersecting(otherRect))
	{
		return;
	}

	// Calculate difference in each edge
	float dLeft = abs(otherRect.left - wallRect.right);
	float dRight = abs(otherRect.right - wallRect.left);
	float dTop = abs(otherRect.top - wallRect.bottom);
	float dBottom = abs(otherRect.bottom - wallRect.top);

	// Collision with bottom of human
	if (dBottom == fmin(dLeft, fmin(dRight, fmin(dTop, dBottom))))
	{
		Player::GetInstance()->SetHasKey(true);
		SetPosition({ -100, -100 });
	}
	// Collision with top of human
	else if (dTop == fmin(dRight, fmin(dTop, dLeft)))
	{
		Player::GetInstance()->SetHasKey(true);
		SetPosition({ -100, -100 });
	}
	// Collision with left of human
	else if (dLeft == fmin(dLeft, dRight))
	{
		Player::GetInstance()->SetHasKey(true);
		SetPosition({ -100, -100 });
	}
	// Collision with right of human
	else
	{
		Player::GetInstance()->SetHasKey(true);
		SetPosition({ -100, -100 });
	}
}

void LKey::Render()
{
	GraphicsManager::GetInstance()->DrawRectangle(SGD::Rectangle(GetPos(), GetSize()), { 255, 255, 255, 255 });
}

void LKey::HandleCollision(Object * _object)
{
	
}