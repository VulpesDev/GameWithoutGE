#include<iostream>
#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\System.hpp"

	class Player {
	private:
		sf::Texture currentTexture;
		sf::Texture textureIdle;
		sf::Texture textureMLR;
		sf::Texture textureMUD;
		int timer = 0;
		int timerMAX = 10;
		float speed = 300.f;
		sf::Clock clock;
		float dt = 0.f;

		
		int idleState = 0;
		enum MovementDirectionMUD { Down, Up };
		enum MovementDirectionMLR { Left, Right};
		sf::Vector2i source = sf::Vector2i(0, Down);
		void Animator();
	public:
		bool canMove = true;
		sf::Sprite sprite;
		sf::FloatRect nextPos;
		sf::Vector2f velocity;
		Player(sf::RenderWindow &window);
		void Update();
		void GoDown();
		void GoUp();
		void GoLeft();
		void GoRight();
	};