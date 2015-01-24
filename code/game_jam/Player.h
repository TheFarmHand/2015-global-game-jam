#pragma once

#include "WRAPPERS\SGD_GraphicsManager.h"
#include "Object.h"

using namespace SGD;


class Player : public Object
{
	Point m_ptStartPosition;
	float m_fGravity;
	Vector m_vtVelocity;
	bool m_bHasKey;
	bool m_BLookingRight;
	bool m_bIsInAir;
	HAudio m_audJump;
	//Fix Jittering in Collission with Gravity
	bool m_bJumping;
	float m_fJumpCount;
public:
	//Singleton
	static Player* GetInstance();

	void Update(float elapsedTime);
	void Input();
	void Render(void);
	void ApplyGravity();

	Point GetStartPos() { return m_ptStartPosition; }
	Vector GetVelocity() { return m_vtVelocity; }

	void SetVelocity(Vector _Vel) { m_vtVelocity = _Vel; }
	void SetIsInAir(bool _Air) { m_bIsInAir = _Air; }
	void SetHasKey(bool _Has) { m_bHasKey = _Has; }

	bool IsJumping() { return m_bJumping; }
	bool HasKey() { return m_bHasKey; }

	Player();
	~Player();
};

