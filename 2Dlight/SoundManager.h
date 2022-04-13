#include"SFML\Audio.hpp"
#include<iostream>
class SoundManager {
private:

public:
	SoundManager();
	sf::Music music;
	sf::SoundBuffer typeChar;
	sf::SoundBuffer typeUChar;
	sf::Sound bobChannel;
	void PlayTypeSound();
	void PlayUpperTypeSound();
	void PlayMain();
};
