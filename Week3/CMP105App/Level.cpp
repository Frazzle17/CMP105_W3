#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	xMover.setFillColor(sf::Color::Red);
	xMover.setRadius(5);
	xMover.setPosition(0, 50);
	xMoverSpeed = 1000.f;

	keyMover.setFillColor(sf::Color::Blue);
	keyMover.setRadius(10);
	keyMover.setPosition(0, 100);
	keyMoverXSpeed = 0.f;
	keyMoverYSpeed = 0.f;

	fourMover.setFillColor(sf::Color::Green);
	fourMover.setRadius(15);
	fourMover.setPosition(0, 150);
	fourMoverXSpeed = 0.f;
	fourMoverYSpeed = 0.f;
	bool pressed = false;
	float cooldown = 0.f;

	if (!font.loadFromFile("font/arial.ttf"))
	{
		std::cout << "Error Loading Font" << std::endl;
	}
	speedText.setFont(font);
	speedText.setCharacterSize(24);
	speedText.setFillColor(sf::Color::White);
	speedText.setString("");
}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	keyMoverXSpeed = 0.f;
	keyMoverYSpeed = 0.f;
	if (input->isKeyDown(sf::Keyboard::Up))
	{
		keyMoverYSpeed = -1000.f;
	}
	if (input->isKeyDown(sf::Keyboard::Down))
	{
		keyMoverYSpeed = 1000.f;
	}
	if (input->isKeyDown(sf::Keyboard::Left))
	{
		keyMoverXSpeed = -1000.f;
	}
	if (input->isKeyDown(sf::Keyboard::Right))
	{
		keyMoverXSpeed = 1000.f;
	}

	if (cooldown < 0.2 && pressed == true)
	{
		cooldown += dt;
	}
	else
	{
		cooldown = 0.0;
		pressed = false;
	}

	if (input->isKeyDown(sf::Keyboard::Equal) && pressed == false)
	{
		if (fourMoverXSpeed >= 0)
		{
			fourMoverXSpeed += 100.0;
		}
		else if (fourMoverXSpeed < 0)
		{
			fourMoverXSpeed -= 100.0;
		}
		if (fourMoverYSpeed >= 0)
		{
			fourMoverYSpeed += 100.0;
		}
		else if (fourMoverYSpeed < 0)
		{
			fourMoverYSpeed -= 100.0;
		}
		pressed = true;
	}
	if (input->isKeyDown(sf::Keyboard::Dash) && pressed == false)
	{
		if (fourMoverXSpeed > 0)
		{
			fourMoverXSpeed -= 100.0;
		}
		else if (fourMoverXSpeed < 0)
		{
			fourMoverXSpeed += 100.0;
		}
		if (fourMoverYSpeed > 0)
		{
			fourMoverYSpeed -= 100.0;
		}
		else if (fourMoverYSpeed < 0)
		{
			fourMoverYSpeed += 100.0;
		}
		if (fourMoverXSpeed == 0 && fourMoverYSpeed == 0)
		{
			fourMoverXSpeed = 0;
			fourMoverYSpeed = 0;
		}
		pressed = true;
	}
	if (!input->isKeyDown(sf::Keyboard::Equal) && !input->isKeyDown(sf::Keyboard::Dash) && pressed == true)
	{
		pressed = false;
	}
}

// Update game objects
void Level::update(float dt)
{
	xMover.move(xMoverSpeed * dt, 0);
	sf::Vector2u windowPos = window->getSize();
	sf::Vector2f xMoverPos = xMover.getPosition();
	if (xMoverPos.x >= (windowPos.x-10) || xMoverPos.x <= 0)
	{
		xMoverSpeed *= -1;
		if (xMoverPos.x > windowPos.x - 10)
		{
			xMoverPos.x = windowPos.x - 10;
		}
		if (xMoverPos.x < 0)
		{
			xMoverPos.x = 0;
		}
		xMover.setPosition(xMoverPos);
	}

	keyMover.move(keyMoverXSpeed * dt, keyMoverYSpeed * dt);
	sf::Vector2f keyMoverPos = keyMover.getPosition();
	if (keyMoverPos.x > windowPos.x - 20)
	{
		keyMoverPos.x = windowPos.x - 20;
	}
	if (keyMoverPos.x < 0)
	{
		keyMoverPos.x = 0;
	}
	if (keyMoverPos.y > windowPos.y - 20)
	{
		keyMoverPos.y = windowPos.y - 20;
	}
	if (keyMoverPos.y < 0)
	{
		keyMoverPos.y = 0;
	}
	keyMover.setPosition(keyMoverPos);

	fourMover.move(fourMoverXSpeed * dt, fourMoverYSpeed * dt);
	sf::Vector2f fourMoverPos = fourMover.getPosition();
	if (fourMoverPos.x > windowPos.x - 30)
	{
		fourMoverPos.x = windowPos.x - 30;
		fourMoverXSpeed *= -1;
	}
	if (fourMoverPos.x < 0)
	{
		fourMoverPos.x = 0;
		fourMoverXSpeed *= -1;
	}
	if (fourMoverPos.y > windowPos.y - 30)
	{
		fourMoverPos.y = windowPos.y - 30;
		fourMoverYSpeed *= -1;
	}
	if (fourMoverPos.y < 0)
	{
		fourMoverPos.y = 0;
		fourMoverYSpeed *= -1;
	}
	fourMover.setPosition(fourMoverPos);

	std::string output = "Speed: ";
	int num = fourMoverXSpeed;
	if (num < 0)
	{
		num *= -1;
	}
	output.append(std::to_string(num));
	speedText.setString(output);
}

// Render level
void Level::render()
{
	beginDraw();

	window->draw(xMover);
	window->draw(keyMover);
	window->draw(fourMover);
	window->draw(speedText);

	endDraw();
}

// clear back buffer
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}