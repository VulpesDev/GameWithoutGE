#include "Brick.h"

using namespace sf;
Brick::Brick()
{
	if (!texture.loadFromFile("Materials/Map/Brick.png"))
	{
		std::cout << "Cannot load texture: 'Brick.png' " << std::endl;
	}
	sprite.setTexture(texture);
	sprite.setScale(Vector2f(2.f, 2.f));
}
void Brick::CheckForPlayer(Sprite playerSprite, float minDistance) {
	Vector2f distance = playerSprite.getPosition() - sprite.getPosition();

	if (std::abs(distance.x) <= minDistance && std::abs(distance.y) <= minDistance)
	{
		canDraw = false;
	}
	else canDraw = true;
}
