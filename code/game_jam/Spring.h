#pragma once

#include "Object.h"
#include "WRAPPERS\SGD_Geometry.h"
#include "../game_jam/WRAPPERS/SGD_Declarations.h"
#include "../game_jam/WRAPPERS/SGD_Handle.h"

using namespace SGD;

class Spring : public Object
{
	HTexture m_hSpringRest;
	HTexture m_hSpringActive;
	float m_fBouncePower;
	float m_fBounceTimer;
	int m_nDirection; // 0-right, 1-down, 2-left, 3-up

	// Spring Sounds //
	SGD::HAudio springSound1 = SGD::INVALID_HANDLE;
	SGD::HAudio springSound2 = SGD::INVALID_HANDLE;
	SGD::HAudio springSound3 = SGD::INVALID_HANDLE;
	SGD::HAudio springSound4 = SGD::INVALID_HANDLE;
	SGD::HAudio springSound5 = SGD::INVALID_HANDLE;

	
public:
	void Update(float elapsedTime);
	void Render(void);
	virtual type GetType() const override { return OBJ_Spring; }
	virtual void HandleCollision(Object * _object) override;
	float GetPower() const { return m_fBouncePower; }
	int GetDirection() const { return m_nDirection; }
	void SetPower(float _power) { m_fBouncePower = _power; }
	void SetDirection(int _dir) { m_nDirection = _dir; }
	Spring();
	~Spring();
};

