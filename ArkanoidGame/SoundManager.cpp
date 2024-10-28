#include "SoundManager.h"

namespace ArkanoidGame
{
	void SoundManager::PlaySound(sf::Sound& sound)
	{
		sound.play();
	}

	void SoundManager::SetBounceSound(sf::SoundBuffer& buffer)
	{
		bounceSound.setBuffer(buffer);
	}

	void SoundManager::SetGameOverSound(sf::SoundBuffer& buffer)
	{
		gameOverSound.setBuffer(buffer);
	}

	void SoundManager::PlayBounceSound()
	{
		PlaySound(bounceSound);
	}

	void SoundManager::PlayGameOverSound()
	{
		PlaySound(gameOverSound);
	}
}