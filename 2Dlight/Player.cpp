#include"Player.h"

using namespace sf;

Player::Player(RenderWindow &window)
{
	if (!textureMUD.loadFromFile("Materials/Player/PlayerUD.png"))
	{
		std::cout << "Cannot load texture: 'PlayerUD.png' " << std::endl;
	}
	if (!textureMLR.loadFromFile("Materials/Player/PlayerLR.png"))
	{
		std::cout << "Cannot load texture: 'PlayerLR.png' " << std::endl;
	}
	if (!textureIdle.loadFromFile("Materials/Player/Idle.png"))
	{
		std::cout << "Cannot load texture: 'Idle.png' " << std::endl;
	}
	sprite.setTexture(textureIdle);
	idleState = 3;
	sprite.setScale(Vector2f(2.5f, 2.5f));
	FloatRect rect = sprite.getLocalBounds();
	sprite.setPosition(window.getView().getCenter());
}
void Player::Animator()
{
	if (timer >= timerMAX)
	{
		source.x++;
		timer = 0;
	}
	if (source.x * 22 >= sprite.getTexture()->getSize().x) source.x = 0;
	sprite.setTextureRect(IntRect(source.x * 22, source.y * 31, 22, 31));
	timer++;
}
void Player::Update()
{
	if (canMove)
	{
		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			GoDown();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			GoUp();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			GoLeft();
		}
		else if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			GoRight();
		}
		else
		{
			sprite.setTexture(textureIdle);
			source.y = idleState;
			velocity.x = 0; velocity.y = 0;
		}
	}
	Player::Animator();

	dt = clock.restart().asSeconds();
}

void Player::GoDown()
{
	idleState = 3;
	sprite.setTexture(textureMUD);
	if (source.y != Down) source.y = Down;
	velocity.x = 0;
	velocity.y = speed * dt;
}
void Player::GoUp()
{
	idleState = 2;
	sprite.setTexture(textureMUD);
	if (source.y != Up) source.y = Up;
	velocity.x = 0;
	velocity.y = -speed * dt;
}
void Player::GoLeft()
{
	idleState = 0;
	sprite.setTexture(textureMLR);
	if (source.y != Left) source.y = Left;
	velocity.y = 0;
	velocity.x = -speed * dt;
}
void Player::GoRight()
{
	idleState = 1;
	sprite.setTexture(textureMLR);
	if (source.y != Right) source.y = Right;
	velocity.y = 0;
	velocity.x = speed * dt;
}
