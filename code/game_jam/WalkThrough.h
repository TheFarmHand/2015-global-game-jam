#pragma once

#include "Object.h"

enum WalkThroughEnter{WL_LEFT,WL_RIGHT,WL_TOP,WL_BOTTOM,WL_ALL};

class WalkThrough : Object
{
	WalkThroughEnter m_eEnterSide;

public:
	void Update(float elapsedtime);
	void Render();
	WalkThrough();
	~WalkThrough();
};

