#include "Level.h"
#include "Bird.h"

Level::Level(float _scale)
{
	b2Vec2 gravity(0.0f, 10.0f);
	world = new b2World(gravity);

	objects.push_back(new Object(sf::Vector2f(480, 500), _scale, b2BodyType::b2_staticBody, "Ground.png", world, &mFixtureUserData));

	for (int i = 0; i < 3; ++i)
	{
		objects.push_back(new Object(sf::Vector2f(550 + i * 100, 400), _scale, b2BodyType::b2_dynamicBody, "Ball.png", world, &mFixtureUserData));
	}

	objects.push_back(new Object(sf::Vector2f(450, 400), _scale, b2BodyType::b2_dynamicBody, "Wagon.png", world, &mFixtureUserData));
	objects.push_back(new Object(sf::Vector2f(380, 410), _scale, b2BodyType::b2_dynamicBody, "Wheel.png", world, &mFixtureUserData));
	objects.push_back(new Object(sf::Vector2f(600, 410), _scale, b2BodyType::b2_dynamicBody, "Wheel.png", world, &mFixtureUserData));

	Joint joint(objects[objects.size() - 3], objects[objects.size() - 2], b2Vec2(-2.0f, 1.0f), world);
	Joint jointTwo(objects[objects.size() - 3], objects[objects.size() - 1], b2Vec2(2.0f, 1.0f), world);

	catapult = new Catapult(sf::Vector2f(250, 410));
}

void Level::Render(sf::RenderWindow& _window, float _scale)
{
	for (int i = 0; i < objects.size(); ++i)
	{
		if (objects[i]->PoofIndex > 0)
		{
			if (objects[i]->PoofIndex <= 7) //7 frames of the poof animation
			{
				objects[i]->PoofTimer++;

				if (objects[i]->PoofTimer > 3) //takes 3 calls to get to the next animation frame
				{
					std::stringstream ss;
					ss << "Poof/Poof" << objects[i]->PoofIndex << ".png";
					objects[i]->PoofTimer = 0;
					objects[i]->LoadTexture(ss.str()); //changes the animation
					objects[i]->PoofIndex++;
				}
			}
			else
			{
				//objects[i]->bodyDef.position = b2Vec2(0, 9999);

				continue; //stop the object rendering as it has poofed away
			}
		}
		objects[i]->Render(_window, _scale);
	}
	for (int i = 0; i < birds.size(); ++i)
	{
		birds[i]->Render(_window, _scale);
	}

	catapult->Render(_window);
}

void Level::Update()
{
	world->Step(1 / 60.f, 8, 3);
}

void Level::MouseButtonPressed(sf::RenderWindow& _window)
{

	birds.push_back(new Bird());
	birds[birds.size() - 1]->listener.mFixtureUserData = &mFixtureUserData;
	catapult->LoadBird(birds[birds.size() - 1]);
	catapult->MoveBird(_window);
}

void Level::MouseButtonReleased()
{
	catapult->LaunchBird(30.0f, *world);
}

void Level::MouseMoved(sf::RenderWindow& _window)
{
	catapult->MoveBird(_window);
}
