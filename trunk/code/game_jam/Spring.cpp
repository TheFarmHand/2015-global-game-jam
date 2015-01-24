#include "Spring.h"
#include "Player.h"
#include <math.h>
#include "Data.h"

Spring::Spring()
{
	SetPosition({ 100, 200 });
	SetSize({ 64, 64 });
	SetRect(SGD::Rectangle(GetPos(), GetSize()));
	m_fBouncePower = 800.0f;
	m_nDirection = 1;
}


Spring::~Spring()
{
}

void Spring::Update(float elapsedTime)
{
	Data * data = Data::GetInstance();
	//SGD::Rectangle wallRect = GetRect();
	//SGD::Rectangle otherRect = Player::GetInstance()->GetRect();

	if (data->levels[data->leveliter].springupdate)
	{
		data->levels[data->leveliter].springupdate(elapsedTime);
		return;
	}
	SGD::Rectangle wallRect = GetRect();
	SGD::Rectangle otherRect = Player::GetInstance()->GetRect();

	//if (!wallRect.IsIntersecting(otherRect))
	//{
	//	return;
	//}

	//// Calculate difference in each edge
	//float dLeft = abs(otherRect.left - wallRect.right);
	//float dRight = abs(otherRect.right - wallRect.left);
	//float dTop = abs(otherRect.top - wallRect.bottom);
	//float dBottom = abs(otherRect.bottom - wallRect.top);

	//// Collision with bottom of human
	//if (dBottom == fmin(dLeft, fmin(dRight, fmin(dTop, dBottom))))
	//{
	//	//float delta = wallRect.bottom - myRect.top;
	//	Player::GetInstance()->SetVelocity({ Player::GetInstance()->GetVelocity().x, -m_fBouncePower });
	//	Player::GetInstance()->SetPosition({ Player::GetInstance()->GetPos().x, Player::GetInstance()->GetPos().y - dBottom });

	//	// No longer in the air
	//	Player::GetInstance()->SetIsInAir(true);
	//}
	//// Collision with top of human
	//else if (dTop == fmin(dRight, fmin(dTop, dLeft)))
	//{
	//	//float delta = myRect.bottom - wallRect.top;
	//	//float delta = wallRect.bottom - myRect.top;
	//	Player::GetInstance()->SetVelocity({ Player::GetInstance()->GetVelocity().x, 0.0f });
	//	Player::GetInstance()->SetPosition({ Player::GetInstance()->GetPos().x, Player::GetInstance()->GetPos().y + dTop });

	//	// No longer in the air
	//	Player::GetInstance()->SetIsInAir(false);
	//}
	//// Collision with left of human
	//else if (dLeft == fmin(dLeft, dRight))
	//{
	//	//float delta = myRect.right - wallRect.left;
	//	//float delta = wallRect.bottom - myRect.top;
	//	Player::GetInstance()->SetVelocity({ 0.0f, Player::GetInstance()->GetVelocity().y });
	//	Player::GetInstance()->SetPosition({ Player::GetInstance()->GetPos().x + dLeft, Player::GetInstance()->GetPos().y });

	//	// No longer in the air
	//	Player::GetInstance()->SetIsInAir(false);
	//}
	//// Collision with right of human
	//else
	//{
	//	//float delta = wallRect.right - myRect.left;
	//	Player::GetInstance()->SetVelocity({ 0.0f, Player::GetInstance()->GetVelocity().y });
	//	Player::GetInstance()->SetPosition({ Player::GetInstance()->GetPos().x - dRight, Player::GetInstance()->GetPos().y });

	//	// No longer in the air
	//	Player::GetInstance()->SetIsInAir(false);
	//}
}

void Spring::Render(void)
{
	GraphicsManager::GetInstance()->DrawRectangle(GetRect(), { 255, 255, 255, 0 });
	switch (m_nDirection)
	{
		case 0:
		{
			SGD::Rectangle rect = GetRect();
			rect.left += 48;
			GraphicsManager::GetInstance()->DrawRectangle(rect, { 255, 0, 0, 255 });
			break;
		}
		case 1:
		{
			SGD::Rectangle rect = GetRect();
			rect.top += 48;
			GraphicsManager::GetInstance()->DrawRectangle(rect, { 255, 0, 0, 255 });
			break;
		}
		case 2:
		{
			SGD::Rectangle rect = GetRect();
			rect.right -= 48;
			GraphicsManager::GetInstance()->DrawRectangle(rect, { 255, 0, 0, 255 });
			break;
		}
		case 3:
		{
			SGD::Rectangle rect = GetRect();
			rect.bottom -= 48;
			GraphicsManager::GetInstance()->DrawRectangle(rect, { 255, 0, 0, 255 });
			break;
		}
	}
}
