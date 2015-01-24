#pragma once

#include "Object.h"

class LKey : public Object
{
	HTexture m_hCandyImage;
	HAudio m_hPickup;
	Point m_ptStartPosition;
public:
	void Update(float ElapsedTime);
	void Render();
	void HandleCollision(Object * _object);
	Point GetStartPos(){ return m_ptStartPosition; }
	LKey();
	~LKey();
};

