#pragma once 

#include "Object.h"
#include "../game_jam/WRAPPERS/SGD_Declarations.h"
#include "../game_jam/WRAPPERS/SGD_Handle.h"

class FallingPlatform : public Object
{
	bool m_bTouched;
	float m_fTouchedCounter;
	Vector m_vtVelocity;
	Point m_ptStartPosition;
	SGD::HTexture m_tPlatform;

public:
	void Update(float elapsedTime);
	void Render(void);
	void SetStartPosition(Point _p) { m_ptStartPosition = _p; }
	virtual type GetType() const override { return OBJ_FallingBlock; }
	virtual void HandleCollision(Object * _object) override;
	FallingPlatform();
	~FallingPlatform();
};

