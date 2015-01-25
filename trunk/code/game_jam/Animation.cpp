#include "Animation.h"
#include "Player.h"

Animation::Animation()
{
	m_hImage = GraphicsManager::GetInstance()->LoadTexture("Assets/graphics/PlaceHolder.jpg");
	m_vFrames.push_back(Rectangle(Point( 0, 0 ), Size( 111, 124 )));
	m_vFrames.push_back(Rectangle(Point(121, 0), Size(111, 124)));
	m_vFrames.push_back(Rectangle(Point(245, 0), Size(111, 124)));
	m_vFrames.push_back(Rectangle(Point(356, 0), Size(111, 124)));
	AnimationSpeed = .3f;
	
}


Animation::~Animation()
{
}

void Animation::SetImage(std::string _FileName)
{
	m_hImage = GraphicsManager::GetInstance()->LoadTexture(_FileName.c_str());
}

void Animation::Update(float ElapsedTime)
{
	if (AnimationCount > 0)
	{
		AnimationCount -= ElapsedTime;
	}
	else
	{
		FrameCount++;
		if (FrameCount >= (int)m_vFrames.size())
		{
			FrameCount = 0;
		}
		AnimationCount = AnimationSpeed;
	}
}

void Animation::Render(bool LookingRight)
{
	if (LookingRight)
	{
		GraphicsManager::GetInstance()->DrawTextureSection(m_hImage, m_ptPos, m_vFrames[FrameCount], {}, {}, {}, { .6f, .5f });
	}
	else
	{
		GraphicsManager::GetInstance()->DrawTextureSection(m_hImage, { (m_ptPos.x + m_szSize.width), m_ptPos.y }, m_vFrames[FrameCount], {}, {}, {}, { -.6f, .5f });
	}
	
}