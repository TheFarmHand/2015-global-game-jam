#pragma once

#include "WRAPPERS\SGD_GraphicsManager.h"

using namespace SGD;

enum type{ OBJ_OBJECT,OBJ_Player, OBJ_SolidWall, OBJ_Spring, OBJ_DeathTouch, OBJ_FallingBlock, OBJ_Key };

class Object
{
private:
	
	SGD::Rectangle m_rRect;
	Size m_szSize;
	Point m_ptPosition;
	HTexture m_hImage;
	type m_eType;

public:

	virtual void Update(float elapsedTime);
	virtual void Render(void);
	SGD::Rectangle GetRect() { return m_rRect; }
	Size GetSize() { return m_szSize; }
	void SetSize(Size _Size) { m_szSize = _Size; }
	Point GetPos() { return m_ptPosition; }
	void SetPosition(Point _pt){ m_ptPosition = _pt; }
	void SetRect(SGD::Rectangle _Rect) { m_rRect = _Rect; }
	void SetType(type _Type){ m_eType = _Type; }
	type GetType(){ return m_eType; }
	virtual void HandleCollision(Object * _object);
	Object();
	virtual ~Object();
};

