#pragma once

#include "WRAPPERS\SGD_GraphicsManager.h"
#include "Object.h"
#include "Animation.h"

using namespace SGD;

class Tiles;

class Player : public Object
{
	Animation m_anANIM;
	SGD::Rectangle m_rGOAL;
	bool m_bPassed;
	Point m_ptStartPosition;
	float m_fGravity;
	bool m_bHasKey;
	bool m_BLookingRight;
	HAudio m_audJump;
	//Fix Jittering in Collission with Gravity
	bool m_bJumping;
	float m_fJumpCount;
	float m_fSpringTimer;
	//Fix Walktrhough
	void GoalCollision();

public:
	//Singleton
	static Player* GetInstance();

	void Update(float elapsedTime);
	void Input(Tiles * _tiles);
	void Render(void);
	virtual type GetType() const override { return OBJ_Player; }
	virtual void HandleCollision(Object * _object) override;
	void ApplyGravity(float _dt);
	void Jump();
	float GetJumpTimer(){ return m_fSpringTimer; }
	Point GetStartPos() { return m_ptStartPosition; }
	void SetHasKey(bool _Has) { m_bHasKey = _Has; }

	bool SpaceFree(Vector _offset, Tiles * _tiles);
	bool IsJumping() { return m_bJumping; }
	bool HasKey() { return m_bHasKey; }
	bool Passed() { return m_bPassed; }


	Player();
	~Player();
};

