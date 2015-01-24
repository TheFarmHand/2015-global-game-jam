#pragma once 

#include "Object.h"

class FallingPlatform : public Object
{
	bool m_bTouched;
	float m_fTouchedCounter;
	Vector m_vtVelocity;
	Point m_ptStartPosition;
public:
	void Update(float elapsedTime);
	void Render(void);
	virtual type GetType() const override { return OBJ_FallingBlock; }
	virtual void HandleCollision(Object * _object) override;
	FallingPlatform();
	~FallingPlatform();
};

