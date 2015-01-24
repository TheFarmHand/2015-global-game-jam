#pragma once

#include "Object.h"
#include "WRAPPERS\SGD_GraphicsManager.h"

using namespace SGD;
class DeathTouch : Object
{
	Size m_szSize;
	Point m_ptPosition;
	SGD::Rectangle m_Rect;

public:

	void Update(float ElapsedTime);
	void Render();
	SGD::Rectangle GetRect() { return m_Rect; }
	DeathTouch();
	~DeathTouch();
};

