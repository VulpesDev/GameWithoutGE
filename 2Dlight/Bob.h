#include<thread>
#include"SFML\Graphics.hpp"
#include"SFML\Window.hpp"
#include"SFML\System.hpp"
#include"SoundManager.h"
#include <string>
#include <cctype>


class Bob {
private:
	sf::Texture idleTexture;
	int timer = 0;
	int timerMAX = 10;
	int animState = 0;
	sf::Vector2i source = sf::Vector2i(0, 0);
	void Animator();

	sf::Font font;
	bool typeString = true;
	void SetTextPos();
	void TypeText(int &snum);
	sf::Clock typeClock;
	int lettersWriten = 0;
	int scriptNum = 0;

	void NextSentance();
	std::string verbaScript[27] = {
		"Just...",
		"Whatever you do...",
		"...don't leave this room!",
		" ",												// End of stage 1
		"I told you NOT to!",
		"You are going to break it!",
		"Just don't do it anymore...",
		"Okay?",
		" ",                                           // End of stage 2
		"WHY WOULD YOU DO IT AGAIN?!",
		"Whatever...",
		"It's not like I'm programmed...",
		".... to stop you in any way...",
		" ",                                         //End of stage 3
		"LOOK WHAT YOU HAVE DONE!",
		"The BLOOD...",
		"The blood in my BRAIN...",
		"It HURTS!!",
		"You have to FIX IT...",
		"Or else..",
		"...we are going to die",
		" ",                                           //End of stage 4
		"Still not fixed...",
		" ",                                            //End of stage 5
		"...Oh...",
		"You fixed it?",
		" ",                                          //End of stage 6
	};

	SoundManager sm;

public:
	bool pCanLeave = false;
	int stageNum = 1;
	sf::Text text;
	sf::Sprite sprite;
	Bob(sf::RenderWindow &window);
	void Update();
};
