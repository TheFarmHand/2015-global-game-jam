#pragma once

#include "Object.h"

enum WalkThroughEnter{WL_LEFT,WL_RIGHT,WL_TOP,WL_BOTTOM,WL_ALL};

class WalkThrough : Object
{
	WalkThroughEnter m_eBlockSide;

public:
	void Update(float elapsedtime);
	void Render();
	virtual type GetType() const override { return OBJ_Walkthrough; }
	WalkThrough();
	~WalkThrough();
};

