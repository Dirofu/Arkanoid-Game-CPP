#pragma once
#include <SFML/Audio.hpp>

namespace ArkanoidGame
{
	class SoundManager
	{
	private:
		sf::Sound bounceSound;
		sf::Sound gameOverSound;
		void PlaySound(sf::Sound& sound);

	public:
		void SetBounceSound(sf::SoundBuffer& buffer);
		void SetGameOverSound(sf::SoundBuffer& buffer);
		void PlayBounceSound();
		void PlayGameOverSound();
	};
}