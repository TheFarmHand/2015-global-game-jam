#include "Animation.h"
#include "WRAPPERS\SGD_AudioManager.h"
#include "Player.h"

Animation::Animation()
{
	m_hImage = GraphicsManager::GetInstance()->LoadTexture("Assets/graphics/STICKMAN_ANIM.png");
	m_hSteps[0] = AudioManager::GetInstance()->LoadAudio("Assets/Audio/Footsteps_Comp_02.wav");
	m_hSteps[1] = AudioManager::GetInstance()->LoadAudio("Assets/Audio/Footsteps_Comp_06.wav");
	m_hSteps[2] = AudioManager::GetInstance()->LoadAudio("Assets/Audio/Footsteps_Comp_08.wav");
	m_hSteps[3] = AudioManager::GetInstance()->LoadAudio("Assets/Audio/Footsteps_Comp_10.wav");
	m_vFrames.push_back(Rectangle(Point( 0, 0 ), Size( 45, 63 )));
	m_vFrames.push_back(Rectangle(Point(42, 0), Size(61, 63)));
	m_vFrames.push_back(Rectangle(Point(102, 0), Size(44, 63)));
	m_vFrames.push_back(Rectangle(Point(145, 0), Size(63, 63)));
	m_vFrames.push_back(Rectangle(Point(208, 0), Size(69, 63)));
	m_vFrames.push_back(Rectangle(Point(281, 0), Size(41, 63)));
	m_vFrames.push_back(Rectangle(Point(322, 0), Size(57, 63)));
	m_vFrames.push_back(Rectangle(Point(380, 0), Size(49, 57)));
	m_vFrames.push_back(Rectangle(Point(429, 0), Size(71, 60)));
	AnimationSpeed = .1;
	
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
		if (FrameCount % 2)
		{
			AudioManager::GetInstance()->PlayAudio(m_hSteps[rand() % 4]);
		}
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
		GraphicsManager::GetInstance()->DrawTextureSection(m_hImage, m_ptPos, m_vFrames[FrameCount], {}, {}, {}, { 1, 1 });
	}
	else
	{
		GraphicsManager::GetInstance()->DrawTextureSection(m_hImage, { (m_ptPos.x + m_szSize.width), m_ptPos.y }, m_vFrames[FrameCount], {}, {}, {}, { -1, 1 });
	}
	
}