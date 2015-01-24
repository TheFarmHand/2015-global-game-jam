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
	bool m_bIsINair;
	HAudio m_audJump;

public:
	//Singleton
	static Player* GetInstance();

	void Update(float elapsedTime);
	void Render(float elapsedTime);
	void Input();
	void Render(void);
	void ApplyGravity();
	SGD::Rectangle GetRect() { return m_recRect; }
	Point GetStartPos() { return m_ptStartPosition; }
	void SetPosition(Point _pt){ m_ptPosition = _pt; }
	void SetVelocity(Vector _Vel) { m_vtVelocity = _Vel; }
	Player();
	~Player();
};

