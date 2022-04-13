#include"SoundManager.h"

SoundManager::SoundManager() {
	if (!music.openFromFile("Materials/Music&Sounds/Meet_Bob.wav")) //Load and start playing music
	{
		std::cout << "Cannot load sound: Meet_Bob.wav";
	}
	music.setLoop(true);
	music.setVolume(50);

	if (!typeChar.loadFromFile("Materials/Music&Sounds/TypeChar.wav"))
	{
		std::cout << "Cannot load sound: TypeChar.wav";
	}
	if (!typeUChar.loadFromFile("Materials/Music&Sounds/UpperChar.wav"))
	{
		std::cout << "Cannot load sound: UpperChar.wav";
	}
}
void SoundManager::PlayMain() {
	music.play();
}
void SoundManager::PlayTypeSound() {
	bobChannel.setBuffer(typeChar);
	bobChannel.setVolume(60);
	bobChannel.play();
}
void SoundManager::PlayUpperTypeSound() {
	bobChannel.setBuffer(typeUChar);
	bobChannel.setVolume(60);
	bobChannel.play();
}