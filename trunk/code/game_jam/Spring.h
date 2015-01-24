#pragma once

#include "Object.h"
#include "WRAPPERS\SGD_Geometry.h"

using namespace SGD;

class Spring : public Object
{
	float m_fBouncePower;
	int m_nDirection; // 0-right, 1-down, 2-left, 3-up
public:
	void Update(float elapsedTime);
	void Render(void);
	virtual type GetType() const override { return OBJ_Spring; }
	float GetPower() const { return m_fBouncePower; }
	int GetDirection() const { return m_nDirection; }
	void SetPower(float _power) { m_fBouncePower = _power; }
	void SetDirection(int _dir) { m_nDirection = _dir; }
	Spring();
	~Spring();
};

