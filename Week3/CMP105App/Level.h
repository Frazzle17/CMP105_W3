#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include <string.h>
#include <iostream>


class Level{
public:
	Level(sf::RenderWindow* hwnd, Input* in);
	~Level();

	void handleInput(float dt);
	void update(float dt);
	void render();

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;

	sf::CircleShape xMover;
	float xMoverSpeed;

	sf::CircleShape keyMover;
	float keyMoverXSpeed;
	float keyMoverYSpeed;

	sf::CircleShape fourMover;
	float fourMoverXSpeed;
	float fourMoverYSpeed;
	bool pressed;
	float cooldown;

	sf::Text speedText;
	sf::Font font;
};