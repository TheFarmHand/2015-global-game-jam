#include "Player.h"
#include "WRAPPERS\SGD_InputManager.h"

Player::Player()
{
	m_ptPosition = { 200, 200 };
	m_ptStartPosition = { 200, 200 };
	m_szSize = { 64, 64 };
	m_vtVelocity = { 0, 0 };
	m_fGravity = 20;
	m_bIsInAir = true;
	m_recRect = Rectangle(m_ptPosition, m_szSize);
}


Player::~Player()
{
}

void Player::Update(float elapsedTime)
{
	
	Input();

	ApplyGravity();

	m_ptPosition += m_vtVelocity * elapsedTime;

	//For Testing Without Collision
	if (m_ptPosition.y > 500 )
	{
		m_bIsInAir = false;
  		m_ptPosition.y = 500;
	}
	if (m_fJumpCount > 0)
	{
		m_fJumpCount -= elapsedTime;
	}
	else
	{
		m_bJumping = false;
	}
	m_recRect = Rectangle(m_ptPosition, m_szSize);
}

Player* Player::GetInstance(void)
{
	static Player s_Instance; //This is stored ONCE in global memory
	return &s_Instance;
}

void Player::Input()
{
	
	if (InputManager::GetInstance()->IsKeyDown(Key::D))
	{
		m_vtVelocity.x = 300;
	}
	else if (InputManager::GetInstance()->IsKeyDown(Key::A))
	{
		m_vtVelocity.x = -300;
	}
	else
	{
		m_vtVelocity.x = 0;
	}

	if (InputManager::GetInstance()->IsKeyPressed(Key::Space) && !m_bIsInAir)
	{
        m_vtVelocity.y = -800;
		m_bIsInAir = true;
		m_bJumping = true;
		m_fJumpCount = 1;
	}
}

void Player::ApplyGravity()
{
	m_vtVelocity.y += m_fGravity;	
	//if (!m_bJumping)
	//{
	//	m_vtVelocity.y = 0;
	//}
}

void Player::Render()
{
	GraphicsManager::GetInstance()->DrawRectangle(m_recRect, { 255, 0, 255, 0 });
}