#include"Map1.h"

using namespace sf;


Map1::Map1() {
	
}

void Map1::BuildLevel1(RenderWindow &window)
{
	const int length = 18;
	//Up
	for (int i = 1; i < length; i++)
	{
		bricksU[i].sprite.setPosition(Vector2f(bricksU[i - 1].sprite.getPosition().x +
			bricksU[i - 1].sprite.getGlobalBounds().width, 0));
		if(bricksU[i].canDraw)window.draw(bricksU[i].sprite);
	}
	//Down
	for (int i = 1; i < length; i++)
	{
		bricksD[i].sprite.setPosition(Vector2f(bricksD[i - 1].sprite.getPosition().x +
			bricksD[i - 1].sprite.getGlobalBounds().width,
			window.getSize().y - bricksD[i - 1].sprite.getGlobalBounds().height));
		if (bricksD[i].canDraw)window.draw(bricksD[i].sprite);
	}
	//Left
	for (int i = 0; i < length; i++)
	{
		if (i != 0) bricksL[i].sprite.setPosition(
			Vector2f(0, bricksL[i-1].sprite.getPosition().y 
				+ bricksL[i - 1].sprite.getGlobalBounds().height));
		if(bricksL[i].canDraw)window.draw(bricksL[i].sprite);
	}
	//Right
	for (int i = 0; i < length; i++)
	{
		if (i != 0) bricksR[i].sprite.setPosition(
			Vector2f(window.getSize().x - bricksR[i].sprite.getGlobalBounds().width,
				bricksR[i - 1].sprite.getPosition().y
				+ bricksR[i - 1].sprite.getGlobalBounds().height));
		else
		{
			bricksR[i].sprite.setPosition(Vector2f(window.getSize().x -
				bricksR[i].sprite.getGlobalBounds().width, 0));
		}
		if (bricksR[i].canDraw)window.draw(bricksR[i].sprite);
	}
}