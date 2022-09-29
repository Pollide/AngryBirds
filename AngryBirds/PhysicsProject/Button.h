#pragma once
#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
using namespace std;

enum button_state // Three possible states for buttons; for color change and detection of press/hover
{
	IDLE = 0,
	HOVER,
	PRESSED
};


class Button
{
public:
	struct Transform
	{
		float x = 600;
		float y = 30;
		float _width = 160;
		float _height = 50;
		sf::Font* font;
		float characterSize = 22;
	};
	// Constructor which takes every variables to be applied to a created button
	Button(Transform transform, string _text, sf::Color _idleColor, sf::Color _hoverColor, sf::Color _pressedColor, int _status = 0, bool _is_title = false);
	~Button();

	// Returns true if the button's state is PRESSED
	const bool isPressed() const;
	// Updates the button's state based on mouse location and mouse press. Changes button's color accordingly
	void update(const sf::Vector2f _mousePos);
	// Draws button and its text at target window
	void render(sf::RenderTarget* target);
	void set_text(string _text);
	int menu;
	bool is_title;
	string ButtonText;
	short unsigned buttonState; // Variable to hold enum's current button state

private:

	// Button's visual variables
	sf::Font* buttonFont;
	sf::RectangleShape buttonShape;
	sf::Text buttonText;
	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Color pressedColor;
};