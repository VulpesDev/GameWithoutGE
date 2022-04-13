#define NOMINMAX
#include<algorithm>
#include<iostream>
#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\System.hpp"

class Brick {
private:
	sf::Texture texture;
public:
	sf::Sprite sprite;
	bool isExit = false;
	bool canDraw = true;
	void CheckForPlayer(sf::Sprite playerSprite, float minDistance);
	Brick();
};