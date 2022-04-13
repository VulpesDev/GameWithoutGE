#include"Player.h"
#include"Map1.h"
#include"Bob.h"
#include<cstdlib>

using namespace sf;

RenderWindow window(sf::VideoMode(900, 840), "2DLight");
View view(Vector2f(0.f, 0.f), Vector2f(900.f, 840.f));
Clock clockk;
float dt;
bool setPath = false;
const float minDistance = 100.f;
enum AutoWalk { None, Up, Down, Right, Left};
AutoWalk aw = None;
int r, r2;

void SetPath(Map1 *map1)
{
	setPath = true;
	 r = rand() % 4;
	 r2 = rand() % 12 + 2;
	switch (r)
	{
	case 0:
		map1->bricksU[r2].isExit = true;
		map1->bricksU[r2+1].isExit = true;
		break;
	case 1:
		map1->bricksD[r2].isExit = true;
		map1->bricksD[r2+1].isExit = true;
		break;
	case 2:
		map1->bricksL[r2].isExit = true;
		map1->bricksL[r2+1].isExit = true;
		break;
	case 3:
		map1->bricksR[r2].isExit = true;
		map1->bricksR[r2+1].isExit = true;
		break;
	}
}

void StopWalking(Player &p, Bob &bob, Map1 *map1) {
	std::this_thread::sleep_for(std::chrono::milliseconds(800));
	p.canMove = true;
	aw = None;
	bob.stageNum++;
	
	switch (r)
	{
	case 0:
		for (int i = 0; i < sizeof(map1->bricksU) / sizeof(map1->bricksU[0]); i++)
		{
			if (map1->bricksU[i].isExit)
				map1->bricksD[i].isExit = false;
		}
		map1->bricksU[r2].isExit = false;
		map1->bricksU[r2 + 1].isExit = false;
		break;
	case 1:
		for (int i = 0; i < sizeof(map1->bricksD) / sizeof(map1->bricksD[0]); i++)
		{
			if (map1->bricksD[i].isExit)
				map1->bricksU[i].isExit = false;
		}
		map1->bricksD[r2].isExit = false;
		map1->bricksD[r2 + 1].isExit = false;
		break;
	case 2:
		for (int i = 0; i < sizeof(map1->bricksL) / sizeof(map1->bricksL[0]); i++)
		{
			if (map1->bricksL[i].isExit)
				map1->bricksR[i].isExit = false;
		}
		map1->bricksL[r2].isExit = false;
		map1->bricksL[r2 + 1].isExit = false;
		break;
	case 3:
		for (int i = 0; i < sizeof(map1->bricksR) / sizeof(map1->bricksR[0]); i++)
		{
			if (map1->bricksR[i].isExit)
				map1->bricksL[i].isExit = false;
		}
		map1->bricksR[r2].isExit = false;
		map1->bricksR[r2 + 1].isExit = false;
		break;
	}
	std::this_thread::sleep_for(std::chrono::seconds(1));
	setPath = false;
}

bool start = false;
void Start(SoundManager &sm) {
	start = true;
	sm.PlayMain();
}

int main()
{
	srand(time(0));
	window.setFramerateLimit(60);

	Player p(window);
	Map1 *map1 = new Map1();
	Bob bob(window);
	SoundManager sm;
	if (!start)Start(sm);


	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
			if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
			{
				window.close();
			}
		}
		if (!setPath && bob.pCanLeave)SetPath(map1);
		p.Update();
		bob.Update();
		if(bob.stageNum >= 8)

		if (aw == Up) p.GoUp();
		else if (aw == Down) p.GoDown();
		else if (aw == Right) p.GoRight();
		else if (aw == Left) p.GoLeft();

		if (p.sprite.getPosition().y + p.sprite.getGlobalBounds().height < 0.f && p.canMove)
		{
			std::cout << "Player is out!" << std::endl;
			p.sprite.setPosition(p.sprite.getPosition().x ,window.getSize().y);
			for (int i = 0; i < sizeof(map1->bricksU)/sizeof(map1->bricksU[0]); i++)
			{
				if(map1->bricksU[i].isExit)
				map1->bricksD[i].isExit = true;
			}
			p.canMove = false;
			aw = Up;
			std::thread t1(StopWalking, std::ref(p), std::ref(bob), std::ref(map1)); t1.detach();
		}
		if (p.sprite.getPosition().y > window.getSize().y && p.canMove)
		{
			std::cout << "Player is out!" << std::endl;
			p.sprite.setPosition(p.sprite.getPosition().x, 0 - p.sprite.getGlobalBounds().height);
			for (int i = 0; i < sizeof(map1->bricksD) / sizeof(map1->bricksD[0]); i++)
			{
				if (map1->bricksD[i].isExit)
					map1->bricksU[i].isExit = true;
			}
			p.canMove = false;
			aw = Down;
			std::thread t1(StopWalking, std::ref(p), std::ref(bob), std::ref(map1)); t1.detach();
		}
		if (p.sprite.getPosition().x > window.getSize().x && p.canMove)
		{
			std::cout << "Player is out!" << std::endl;
			p.sprite.setPosition(0 - p.sprite.getGlobalBounds().width, p.sprite.getPosition().y);
			for (int i = 0; i < sizeof(map1->bricksR) / sizeof(map1->bricksR[0]); i++)
			{
				if (map1->bricksR[i].isExit)
					map1->bricksL[i].isExit = true;
			}
			p.canMove = false;
			aw = Right;
			std::thread t1(StopWalking, std::ref(p), std::ref(bob), std::ref(map1)); t1.detach();
		}
		if (p.sprite.getPosition().x + p.sprite.getGlobalBounds().width < 0.f && p.canMove)
		{
			std::cout << "Player is out!" << std::endl;
			p.sprite.setPosition(window.getSize().x, p.sprite.getPosition().y);
			for (int i = 0; i < sizeof(map1->bricksL) / sizeof(map1->bricksL[0]); i++)
			{
				if (map1->bricksL[i].isExit)
					map1->bricksR[i].isExit = true;
			}
			p.canMove = false;
			aw = Left;
			std::thread t1(StopWalking, std::ref(p), std::ref(bob), std::ref(map1)); t1.detach();
		}


		window.setView(view);
		view.setCenter(Vector2f(window.getSize().x / 2.f, window.getSize().y / 2.f));
		if (view.getRotation() < 180 && bob.stageNum == 4)
			view.rotate(1.f);
		else if (view.getRotation() > 0 && bob.stageNum == 6)
			view.rotate(-1.f);

		//Collisions
		FloatRect playerBounds = p.sprite.getGlobalBounds();
		p.nextPos = playerBounds;
		p.nextPos.left += p.velocity.x;
		p.nextPos.top += p.velocity.y;


		for (int i = 0; i < 18; i++)
		{
			//CheckForPlayer
			if (map1->bricksU[i].isExit)
			{
				map1->bricksU[i].CheckForPlayer(p.sprite, minDistance);
			}
			if (map1->bricksD[i].isExit)
			{
				map1->bricksD[i].CheckForPlayer(p.sprite, minDistance);
			}
			if (map1->bricksL[i].isExit)
			{
				map1->bricksL[i].CheckForPlayer(p.sprite, minDistance);
			}
			if (map1->bricksR[i].isExit)
			{
				map1->bricksR[i].CheckForPlayer(p.sprite, minDistance);
			}
			//Collisions
			FloatRect brickBoundsU = map1->bricksU[i].sprite.getGlobalBounds();
			FloatRect brickBoundsD = map1->bricksD[i].sprite.getGlobalBounds();
			FloatRect brickBoundsL = map1->bricksL[i].sprite.getGlobalBounds();
			FloatRect brickBoundsR = map1->bricksR[i].sprite.getGlobalBounds();

			if( (brickBoundsU.intersects(p.nextPos) && !map1->bricksU[i].isExit)
				|| (brickBoundsD.intersects(p.nextPos) && !map1->bricksD[i].isExit)
				|| (brickBoundsL.intersects(p.nextPos) && !map1->bricksL[i].isExit)
				|| (brickBoundsR.intersects(p.nextPos) && !map1->bricksR[i].isExit))
			{
				p.velocity.x = 0.f;
				p.velocity.y = 0.f;
			}
		}
		p.sprite.move(p.velocity);
		

		window.clear(Color::Black);

		(*map1).BuildLevel1(window);
		window.draw(p.sprite);
		window.draw(bob.sprite);
		window.draw(bob.text);

		window.display();

		dt = clockk.restart().asSeconds();
	}
}