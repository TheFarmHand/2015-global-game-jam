#pragma once

#include "Object.h"

class LKey : Object
{
	HTexture m_hCandyImage;
	HAudio m_hPickup;
	Point StartPosition;
public:
	void Update(float ElapsedTime);
	void Render();
	void HandleCollision(Object * _object);
	LKey();
	~LKey();
};

