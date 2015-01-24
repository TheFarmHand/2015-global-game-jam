#include "Player.h"
#include <iostream>
#include "WRAPPERS\SGD_InputManager.h"

Player::Player()
{
	SetPosition({ 200, 200 });
	m_ptStartPosition = { 200, 200 };
	SetSize({ 64, 64 });
	SetVelocity({ 0.0f, 0.0f });
	m_fGravity = 1500.0f;
	SetIsInAir(true);
	m_bHasKey = false;
	SetRect(Rectangle(GetPos(), GetSize()));
}


Player::~Player()
{
}

void Player::Update(float elapsedTime)
{
	Input();

	

	if (GetInAir())
	{
		ApplyGravity(elapsedTime);
	}

	float position = GetPos().x;

	if (m_fJumpCount > 0)
	{
		m_fJumpCount -= elapsedTime;
	}
	else
	{
		m_fJumpCount = .1f;
		std::cout << GetInAir() << "\n";
	}
	Point Temp = GetPos();
	Temp += GetVelocity() * elapsedTime;
	SetPosition(Temp);

	SetRect(Rectangle(GetPos(), GetSize()));

	SetIsInAir(true);
	SetClippedV(false);
	SetClippedH(false);
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
		SetVelocity({ 300, GetVelocity().y });
	}
	else if (InputManager::GetInstance()->IsKeyDown(Key::A))
	{
		SetVelocity({ -300, GetVelocity().y });
	}
	else
	{
		SetVelocity({ 0, GetVelocity().y });
	}

	if (InputManager::GetInstance()->IsKeyPressed(Key::Space) && !GetInAir())
	{
		SetVelocity({ GetVelocity().x, -800 });
		SetIsInAir(true);
		m_bJumping = true;
		m_fJumpCount = .5f;
	}
}

void Player::ApplyGravity(float _dt)
{
	SetVelocity({ GetVelocity().x, GetVelocity().y + m_fGravity * _dt });
	//if (!m_bJumping)
	//{
	//	m_vtVelocity.y = 0;
	//}
}

void Player::Render()
{
	GraphicsManager::GetInstance()->DrawRectangle(GetRect(), { 255, 0, 255, 0 });
}


void Player::HandleCollision(Object * _object)
{
	// Solid wall
	if (_object->GetType() == OBJ_SolidWall)
	{
		BasicCollision(_object);	
	}
	else if (_object->GetType() == OBJ_DeathTouch)
	{
		SetPosition(m_ptStartPosition);
	}
	else if (_object->GetType() == OBJ_FallingBlock)
	{
		BasicCollision(_object);
	}
	else if (_object->GetType() == OBJ_Walkthrough)
	{
		BasicCollision(_object);
	}
}