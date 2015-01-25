#pragma once

#include "Object.h"
#include "../game_jam/WRAPPERS/SGD_Declarations.h"
#include "../game_jam/WRAPPERS/SGD_Handle.h"

class Player;

class LKey : public Object
{
	HTexture m_hCandyImage;
	HTexture m_hKey;
	HAudio m_hPickup;
	Point m_ptStartPosition;
public:
	void Update(float ElapsedTime, Player * _p);
	void ChaseUpdate(float _dt);
	void Render();
	void HandleCollision(Object * _object);
	virtual type GetType() const override { return OBJ_Key; }
	void SetStartPos(SGD::Point _p) { m_ptStartPosition = _p; }
	Point GetStartPos(){ return m_ptStartPosition; }
	LKey();
	~LKey();
};

