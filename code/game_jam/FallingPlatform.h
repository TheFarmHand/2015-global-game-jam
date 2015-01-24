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
	FallingPlatform();
	~FallingPlatform();
};

