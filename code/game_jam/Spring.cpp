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
	SetImage(GraphicsManager::GetInstance()->LoadTexture("Assets/graphics/Trampoline.png"));
	m_hSpringRest = SGD::GraphicsManager::GetInstance()->LoadTexture("Assets/graphics/SpringRest.png");
	m_hSpringActive = SGD::GraphicsManager::GetInstance()->LoadTexture("Assets/graphics/SpringActive.png");
}


Spring::~Spring()
{
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hSpringRest);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hSpringActive);
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
	
	if (m_nDirection == 0)
	{
		GraphicsManager::GetInstance()->DrawTexture(GetImage(), { GetPos().x ,GetPos().y + GetSize().height}, 4.72f, {}, {}, { 2, 2 });
	}
	else
	{
		GraphicsManager::GetInstance()->DrawTexture(GetImage(), GetPos(), {}, {}, {}, { 2, 2 });
	}
}
