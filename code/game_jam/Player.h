#pragma once
#pragma once
#include "WRAPPERS\SGD_GraphicsManager.h"
#include "Object.h"

using namespace SGD;


class Player : public Object
{
	SGD::Rectangle m_recRect;
	Point m_ptStartPosition;
	Size m_szSize;
	float m_fGravity;
	HTexture m_Image;
	Point m_ptPosition;
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
	void Render(float elapsedTime);
	void Input();
	void Render(void);
	void ApplyGravity();
	SGD::Rectangle GetRect() { return m_recRect; }
	Size GetSize() { return m_szSize; }
	Point GetPos() { return m_ptPosition; }
	Point GetStartPos() { return m_ptStartPosition; }
	Vector GetVelocity() { return m_vtVelocity; }
	void SetPosition(Point _pt){ m_ptPosition = _pt; }
	void SetVelocity(Vector _Vel) { m_vtVelocity = _Vel; }
	void SetIsInAir(bool _Air) { m_bIsInAir = _Air; }
	bool IsJumping() { return m_bJumping; }
	Player();
	~Player();
};

