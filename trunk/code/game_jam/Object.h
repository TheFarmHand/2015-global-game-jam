#pragma once

#include "WRAPPERS\SGD_GraphicsManager.h"

using namespace SGD;

enum type{ OBJ_OBJECT,OBJ_Player, OBJ_SolidWall, OBJ_Spring, OBJ_DeathTouch, OBJ_FallingBlock, OBJ_Key, OBJ_Walkthrough,OBJ_GOAL};

class Object
{
private:
	
	SGD::Rectangle m_rRect;
	Size m_szSize;
	Point m_ptPosition;
	Vector m_vtVelocity;
	bool m_bIsInAir;
	bool m_bClippedV;
	bool m_bClippedH;
	HTexture m_hImage;

public:

	virtual void Update(float elapsedTime);
	virtual void Render(void);
	SGD::Rectangle GetRect() { return m_rRect; }
	Size GetSize() { return m_szSize; }
	void SetSize(Size _Size) { m_szSize = _Size; SetRect(SGD::Rectangle(m_ptPosition, m_szSize)); }
	Point GetPos() { return m_ptPosition;  }
	Vector GetVelocity() { return m_vtVelocity; }
	void SetVelocity(Vector _Vel) { m_vtVelocity = _Vel; }
	bool GetInAir() const { return m_bIsInAir; }
	bool GetClippedV() const { return m_bClippedV; }
	bool GetClippedH() const { return m_bClippedH; }
	void SetClippedV(bool _c) { m_bClippedV = _c; }
	void SetClippedH(bool _c) { m_bClippedH = _c; }
	void SetIsInAir(bool _Air) { m_bIsInAir = _Air; }
	void SetPosition(Point _pt){ m_ptPosition = _pt; SetRect(SGD::Rectangle(m_ptPosition, m_szSize)); }
	void SetRect(SGD::Rectangle _Rect) { m_rRect = _Rect; }
	virtual type GetType() const { return OBJ_OBJECT; }
	virtual void HandleCollision(Object * _object);
	void BasicCollision(Object * _other);
	void SetImage(HTexture _Image) { m_hImage = _Image; }
	HTexture GetImage() { return m_hImage; }
	void Move(Vector _delta);
	Object();
	virtual ~Object();
};

