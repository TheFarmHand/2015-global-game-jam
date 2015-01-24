#pragma once

#include "Object.h"
#include "WRAPPERS\SGD_GraphicsManager.h"

using namespace SGD;

class SolidWall : Object
{
public:

	void Update(float ElapsedTime);
	void Render();
	SolidWall();
	~SolidWall();
};

