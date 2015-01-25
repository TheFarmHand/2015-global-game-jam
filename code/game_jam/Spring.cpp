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

	if (m_fBounceTimer > 0.0f)
	{
		m_fBounceTimer -= elapsedTime;
	}

}

void Spring::Render(void)
{
	GraphicsManager * pGraphics = GraphicsManager::GetInstance();

	float rotation = (90.0f * m_nDirection) * (3.14159f / 180.0f);
	if (m_fBounceTimer <= 0.0f)
	{
		pGraphics->DrawTexture(m_hSpringRest, GetPos(), rotation, { 32.0f, 32.0f }, { 255, 255, 255 }, { 1.0f, 1.0f });
	}
	else
	{
		pGraphics->DrawTexture(m_hSpringActive, GetPos(), rotation, { 32.0f, 32.0f }, { 255, 255, 255 }, { 1.0f, 1.0f });
	}
	
	//if (m_nDirection == 0)
	//{
	//	GraphicsManager::GetInstance()->DrawTexture(GetImage(), { GetPos().x ,GetPos().y + GetSize().height}, 4.72f, {}, {}, { 2, 2 });
	//}
	//else
	//{
	//	GraphicsManager::GetInstance()->DrawTexture(GetImage(), GetPos(), {}, {}, {}, { 2, 2 });
	//}
}

void Spring::HandleCollision(Object * _object)
{
	if (_object->GetType() == OBJ_Player)
	{
		m_fBounceTimer = 0.5f;
	}
}