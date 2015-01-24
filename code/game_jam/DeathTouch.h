#pragma once

#include "Object.h"
#include "WRAPPERS\SGD_GraphicsManager.h"

using namespace SGD;
class DeathTouch : public Object
{

public:

	void Update(float ElapsedTime);
	void Render();
	virtual type GetType() const override { return OBJ_DeathTouch; }
	DeathTouch();
	~DeathTouch();
};

