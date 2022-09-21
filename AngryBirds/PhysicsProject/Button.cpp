#include "Button.h"

Button::Button(float x, float y, float _width, float _height, sf::Font* _font, string _text, sf::Color _idleColor, sf::Color _hoverColor, sf::Color _pressedColor, bool _is_options, bool _is_title)
{
	buttonState = IDLE; // Initial state

	is_options = _is_options;
	is_title = _is_title;

	// Position and size
	buttonShape.setPosition(sf::Vector2f(x, y));
	buttonShape.setSize(sf::Vector2f(_width, _height)); // Button is a rectangle of that size

	// Parameters for text within the rectangle
	buttonFont = _font;
	buttonText.setFont(*buttonFont);
	set_text(_text);
	buttonText.setFillColor(is_title ? _idleColor : sf::Color::Black);
	buttonText.setCharacterSize(22 * (is_title ? 2.5f : 1));
	// Placing text in the middle of the rectangle
	buttonText.setPosition(buttonShape.getPosition().x + (buttonShape.getGlobalBounds().width / 2) - buttonText.getGlobalBounds().width / 2, buttonShape.getPosition().y + (buttonShape.getGlobalBounds().height / 2) - buttonText.getGlobalBounds().height / 2 - 5);

	// Passing desired colors for each button state
	idleColor = _idleColor;
	hoverColor = _hoverColor;
	pressedColor = _pressedColor;

	// Setting initial color
	buttonShape.setFillColor(idleColor);
}

void Button::set_text(string _text)
{
	buttonText.setString(_text);
}

Button::~Button()
{
}

const bool Button::isPressed() const
{
	if (buttonState == PRESSED)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Button::update(const sf::Vector2f _mousePos)
{
	buttonState = IDLE; // Goes back to idle state if none of the conditions below are met

	if (buttonShape.getGlobalBounds().contains(_mousePos)) // Check if mouse position is within the rectangle
	{
		buttonState = HOVER; // State changes to hover

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) // Check for mouse left click
		{
			buttonState = PRESSED; // State changes to pressed
		}
	}

	switch (buttonState) // Switch statement to update rectangle color based on its current state
	{
	case IDLE:
		buttonShape.setFillColor(idleColor);
		break;

	case HOVER:
		buttonShape.setFillColor(hoverColor);
		break;

	case PRESSED:
		buttonShape.setFillColor(pressedColor);
		break;

	default:
		buttonShape.setFillColor(sf::Color::Black);
		break;
	}
}

void Button::render(sf::RenderTarget* target)
{
	// Sends rectangle and the text inside of it to be drawn at target
	if (!is_title)
		target->draw(buttonShape);

	target->draw(buttonText);
}