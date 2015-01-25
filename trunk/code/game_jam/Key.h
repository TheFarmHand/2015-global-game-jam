#pragma once

#include "Object.h"
#include "../game_jam/WRAPPERS/SGD_Declarations.h"
#include "../game_jam/WRAPPERS/SGD_Handle.h"

class LKey : public Object
{
	HTexture m_hCandyImage;
	HTexture m_hKey;
	HAudio m_hPickup;
	Point m_ptStartPosition;
public:
	void Update(float ElapsedTime);
	void Render();
	void HandleCollision(Object * _object);
	void SetStartPos(SGD::Point _p) { m_ptStartPosition = _p; }
	Point GetStartPos(){ return m_ptStartPosition; }
	LKey();
	~LKey();
};

