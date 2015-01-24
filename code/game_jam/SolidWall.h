#pragma once

#include "Object.h"
#include "WRAPPERS\SGD_GraphicsManager.h"

using namespace SGD;

class SolidWall : public Object
{
public:

	void Update(float ElapsedTime);
	void Render();
	virtual type GetType() const override { return OBJ_SolidWall; }
	SolidWall();
	~SolidWall();
};

