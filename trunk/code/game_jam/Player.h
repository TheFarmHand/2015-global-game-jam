#pragma once

#include "WRAPPERS\SGD_GraphicsManager.h"
#include "Object.h"
#include "Animation.h"

#include "WRAPPERS\SGD_Declarations.h"


using namespace SGD;

class Tiles;
class GameState;
class Player : public Object
{
	//for inception effect
	float m_fRotation;
	bool m_bInception;
	
	float m_fInceptionCounter;

	SGD::Rectangle m_rGOAL;
	bool m_bPassed;
	Point m_ptStartPosition;
	float m_fGravity;
	bool m_bHasKey;
	bool m_BLookingRight;
	bool m_bDead;
	HAudio m_audJump;
	//Fix Jittering in Collission with Gravity
	bool m_bJumping;
	float m_fJumpCount;
	float m_fSpringTimer;
	float m_fNextLevelTimer;
	bool m_bLevelComplete;
	SGD::HTexture	m_tDoor;
	//Fix Walktrhough
	void GoalCollision();

	bool m_bLandingPlayed;

	// Walking Sounds //
	HAudio walkingSound1 = INVALID_HANDLE;
	HAudio walkingSound2 = INVALID_HANDLE;
	HAudio walkingSound3 = INVALID_HANDLE;
	HAudio walkingSound4 = INVALID_HANDLE;

	// Landing Sounds //
	HAudio landingSound1 = INVALID_HANDLE;
	HAudio landingSound2 = INVALID_HANDLE;
	HAudio landingSound3 = INVALID_HANDLE;
	HAudio landingSound4 = INVALID_HANDLE;
	HAudio landingSound5 = INVALID_HANDLE;
	HAudio landingSound6 = INVALID_HANDLE;

	// Jumping Sounds //
	HAudio jumpingSound1 = INVALID_HANDLE;
	HAudio jumpingSound2 = INVALID_HANDLE;
	HAudio jumpingSound3 = INVALID_HANDLE;

	//Win Sounds
	HAudio m_hWin[2];

public:
	Animation m_anANIM;

	GameState* gamestate = nullptr;
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
	void SetDead(bool _d) { m_bDead = _d; }
	bool GetDead() const { return m_bDead; }
	bool SpaceFree(Vector _offset, Tiles * _tiles);
	bool IsJumping() { return m_bJumping; }
	bool HasKey() { return m_bHasKey; }
	bool Passed() { return m_bPassed; }
	bool GetLookingRight(){ return m_BLookingRight; }
	void SetLookingRight(bool _right){ m_BLookingRight = _right; }
	void OtherCollsision(Object * _object);
	void SetInception(bool _Inception){ m_bInception = _Inception; }
	void SetInceptionCounter(float _FL) { m_fRotation = _FL; }
	bool Inception(){ return m_bInception; }
	void SetPositive(bool _bla){ m_bPositive = _bla; m_fRotation = 0; }
	bool GetPositive(){ return m_bPositive; }
	bool m_bPositive;

	Player();
	~Player();
};

