#pragma once

#include "WRAPPERS\SGD_GraphicsManager.h"
#include <vector>
#include <string>

using namespace SGD;



class Animation
{
	Point m_ptPos;
	Size m_szSize;
	HTexture m_hImage;
	float AnimationSpeed;
	float AnimationCount;
	int FrameCount;
public:
	std::vector<SGD::Rectangle> m_vFrames;
	void Update(float elapsedTime);
	void Render(bool LookingRight);
	void SetImage(std::string);
	void SetPos(Point _Pos) { m_ptPos = _Pos; }
	void SetSize(Size _Size0) { m_szSize = _Size0; }
	Animation();
	~Animation();
};

