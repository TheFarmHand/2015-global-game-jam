#include "Spring.h"
#include "Player.h"
#include <math.h>
#include "Data.h"

#include "WRAPPERS\SGD_AudioManager.h"

Spring::Spring()
{
	SetPosition({ 100, 200 });
	SetSize({ 64, 64 });
	SetRect(SGD::Rectangle(GetPos(), GetSize()));
	m_fBouncePower = 800.0f;
	m_nDirection = 1;
	SetImage(GraphicsManager::GetInstance()->LoadTexture("Assets/graphics/Trampoline.png"));
	m_hSpringRest = SGD::GraphicsManager::GetInstance()->LoadTexture("Assets/graphics/SpringRest.png");
	m_hSpringActive = SGD::GraphicsManager::GetInstance()->LoadTexture("Assets/graphics/SpringActive.png");

	// Spring Sound Initializations //
	springSound1 = SGD::AudioManager::GetInstance()->LoadAudio("Assets/Audio/Spring_Bounce_1.wav");
	springSound2 = SGD::AudioManager::GetInstance()->LoadAudio("Assets/Audio/Spring_Bounce_2.wav");
	springSound3 = SGD::AudioManager::GetInstance()->LoadAudio("Assets/Audio/Spring_Bounce_3.wav");
	springSound4 = SGD::AudioManager::GetInstance()->LoadAudio("Assets/Audio/Spring_Bounce_4.wav");
	springSound5 = SGD::AudioManager::GetInstance()->LoadAudio("Assets/Audio/Spring_Bounce_5.wav");
}


Spring::~Spring()
{
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hSpringRest);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hSpringActive);
}

void Spring::Update(float elapsedTime)
{
	Data * data = Data::GetInstance();
	//SGD::Rectangle wallRect = GetRect();
	//SGD::Rectangle otherRect = Player::GetInstance()->GetRect();

	if (data->levels[data->leveliter].springupdate)
	{
		data->levels[data->leveliter].springupdate(elapsedTime);
		return;
	}
	SGD::Rectangle wallRect = GetRect();
	SGD::Rectangle otherRect = Player::GetInstance()->GetRect();

	if (m_fBounceTimer > 0.0f)
	{
		m_fBounceTimer -= elapsedTime;
	}

}

void Spring::Render(void)
{
	GraphicsManager * pGraphics = GraphicsManager::GetInstance();

	float rotation = (90.0f * m_nDirection) * (3.14159f / 180.0f);
	if (m_fBounceTimer <= 0.0f)
	{
		pGraphics->DrawTexture(m_hSpringRest, GetPos(), rotation, { 32.0f, 32.0f }, { 255, 255, 255 }, { 1.0f, 1.0f });
	}
	else
	{
		pGraphics->DrawTexture(m_hSpringActive, GetPos(), rotation, { 32.0f, 32.0f }, { 255, 255, 255 }, { 1.0f, 1.0f });
	}
	
	//if (m_nDirection == 0)
	//{
	//	GraphicsManager::GetInstance()->DrawTexture(GetImage(), { GetPos().x ,GetPos().y + GetSize().height}, 4.72f, {}, {}, { 2, 2 });
	//}
	//else
	//{
	//	GraphicsManager::GetInstance()->DrawTexture(GetImage(), GetPos(), {}, {}, {}, { 2, 2 });
	//}
}

void Spring::HandleCollision(Object * _object)
{
	SGD::AudioManager* audio = SGD::AudioManager::GetInstance();

	if (_object->GetType() == OBJ_Player)
	{
		m_fBounceTimer = 0.5f;

		// Spring Sound Randomizer //
		int randNum = rand() % 5;

		if (!SGD::AudioManager::GetInstance()->IsAudioPlaying(springSound1) && 
			!SGD::AudioManager::GetInstance()->IsAudioPlaying(springSound2) && 
			!SGD::AudioManager::GetInstance()->IsAudioPlaying(springSound3) && 
			!SGD::AudioManager::GetInstance()->IsAudioPlaying(springSound4) && 
			!SGD::AudioManager::GetInstance()->IsAudioPlaying(springSound5)) // No spring sound is already playing
		{
			if (randNum == 0)
				audio->PlayAudio(springSound1, false);
			else if (randNum == 1)
				audio->PlayAudio(springSound2, false);
			else if (randNum == 2)
				audio->PlayAudio(springSound3, false);
			else if (randNum == 3)
				audio->PlayAudio(springSound4, false);
			else if (randNum == 4)
				audio->PlayAudio(springSound5, false);
		}
	}
}