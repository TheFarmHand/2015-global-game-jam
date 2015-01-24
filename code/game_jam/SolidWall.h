#pragma once

#include "Object.h"
#include "WRAPPERS\SGD_GraphicsManager.h"

using namespace SGD;

class SolidWall
{
	Size m_szSize;
	Point m_ptPosition;
	SGD::Rectangle m_Rect;
public:

	void Update(float ElapsedTime);
	void Render();
	SGD::Rectangle GetRect() { return m_Rect; }
	SolidWall();
	~SolidWall();
};

