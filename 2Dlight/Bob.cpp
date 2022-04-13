#include"Bob.h";


using namespace sf;


void Bob::SetTextPos() {
	FloatRect textRect = text.getLocalBounds();
	text.setOrigin(Vector2f(textRect.left + textRect.width / 2.f,
		textRect.top + textRect.height / 2.f));
	text.setPosition(Vector2f(sprite.getPosition().x + 11.f,
		sprite.getPosition().y - 30.f));
}
Bob::Bob(RenderWindow &window)
{
	if (!idleTexture.loadFromFile("Materials/Player/Bob2.png"))
	{
		std::cout << "Cannot load texture: 'Bob2.png' " << std::endl;
	}
	sprite.setTexture(idleTexture);
	sprite.setScale(Vector2f(2.5f, 2.5f));
	sprite.setPosition(window.getView().getCenter() + Vector2f(200.f, 5.f));

	if (!font.loadFromFile("Materials/UI/PixelFont.ttf"))
	{
		std::cout << "Cannot load font: 'PixelFont.ttf' " << std::endl;
	}
	text.setFont(font);
	SetTextPos();
	text.setString("");
	text.setCharacterSize(20);
}
void Bob::Animator() {
	if (timer >= timerMAX) {
		source.x++;
		timer = 0;
	}
	if (source.x * 22 >= sprite.getTexture()->getSize().x) source.x = 0;
	sprite.setTextureRect(IntRect(source.x * 22, source.y * 31, 22, 31));
	timer++;
}
void Bob::TypeText(int &snum) {
	typeString = false;
	int snum1 = snum;
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
	std::string st = "";
	bool soundb = true;
	for (std::string::iterator it = verbaScript[snum1].begin(); it != verbaScript[snum1].end(); it++)
	{
		//std::cout << *it << ' ';
		if (*it != '.')
		{
			if (std::isupper(*it))
				sm.PlayUpperTypeSound();
			else
				sm.PlayTypeSound();
		}
		st += *it;
		text.setString(st);
		SetTextPos();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	NextSentance();
}
void Bob::NextSentance() {

	if ((stageNum == 1 && scriptNum == 3)
		|| (stageNum == 2 && scriptNum == 8)
		|| (stageNum == 3 && scriptNum == 13)
		|| (stageNum == 4 && scriptNum == 21)
		|| (stageNum == 5 && scriptNum == 23)
		|| (stageNum == 6 && scriptNum == 26)
		|| (stageNum == 7 && scriptNum == 30))
	{
		pCanLeave = true;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		NextSentance();
	}
	else
	{
		pCanLeave = false;
		scriptNum++;
		if (scriptNum == 26) {
			stageNum = 1;
			scriptNum = 0;
		}
		typeString = true;
	}
}
void Bob::Update() {
	Bob::Animator();
	if (typeString) {
		std::thread t1(&Bob::TypeText, this, std::ref(scriptNum));
		t1.detach();
	}

}