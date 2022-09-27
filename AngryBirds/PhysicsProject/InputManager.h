#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Button.h"
#include <sstream>
#include "Scene.h"

class InputManager
{
public:
	void InitializeButtons(sf::Font* font);
	void InitializeMusic();
	void CreateButton(string _text, Button::Transform transform, int _status = 0, bool _is_title = false);
	void UpdateButtons(const sf::RenderWindow* window, Scene* scene);
	void RenderButtons(sf::RenderTarget* target, int* menu);
	std::string CreateString(string attach, int value);
	bool holding;
	const int MaxVolume = 10; //keep above else it will be zero
	int MusicVolume = MaxVolume;
	int SoundVolume = MaxVolume;
	map<string, Button*> buttons;
	sf::Music music;
	sf::Music sound;
};

