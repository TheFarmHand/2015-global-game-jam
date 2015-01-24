#pragma once

#include "Object.h"

enum WalkThroughEnter{WL_LEFT,WL_RIGHT,WL_TOP,WL_BOTTOM,WL_ALL};

class WalkThrough : public Object
{
	WalkThroughEnter m_eBlockSide;

public:
	void Update(float elapsedtime);
	void Render();
	void SetEnter(WalkThroughEnter _enter) { m_eBlockSide = _enter; }
	virtual type GetType() const override { return OBJ_Walkthrough; }
	WalkThrough();
	~WalkThrough();
};

