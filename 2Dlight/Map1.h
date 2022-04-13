#include<iostream>
#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\System.hpp"
#include"Brick.h"

class Map1 {
private:

public:
	Brick bricksU[18];
	Brick bricksD[18];
	Brick bricksL[18];
	Brick bricksR[18];
	Map1();
	void BuildLevel1(sf::RenderWindow &window);
};