#pragma once

#include "Object.h"
#include "WRAPPERS\SGD_Geometry.h"

using namespace SGD;

class Spring : Object
{
	float m_fBouncePower;
public:
	void Update(float elapsedTime);
	void Render(void);
	Spring();
	~Spring();
};

