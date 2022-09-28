#include "Scene.h"
#include "Bird.h"


Scene::Scene()
{
	Initialise();
}

void Scene::Initialise()
{
	b2Vec2 gravity(0.0f, 10.0f);
	world = new b2World(gravity);
	Background = sf::Color(8, 136, 97);
	catapult = new Catapult(sf::Vector2f(250, 410));
}



void Scene::Render(sf::RenderWindow& _window)
{
	int enemiesLeft = 0;
	int birdsLeft = 0;

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

					for (int j = 0; j < world->GetJointCount(); j++) //removes wheels and other connected parts
					{
						//std::cout << "joint";
						if (world->GetJointList()[j].GetBodyB() == objects[i]->body)
						{
							world->DestroyJoint(&world->GetJointList()[j]);
						}
					}

					objects[i]->body->GetFixtureList()->SetSensor(true);
				}
			}
			else
			{
				//objects[i]->bodyDef.position = b2Vec2(0, 9999);

				continue; //stop the object rendering as it has poofed away
			}
		}
		else
		{

			//std::cout << objects[i]->CharacterType << " | ";
			if (objects[i]->CharacterType > 0 && objects[i]->ReturnSpeed(objects[i]->body) < 0.2f)
			{
				objects[i]->PoofIndex = 1;
			}
		}

		if (objects[i]->CharacterType < 0)
		{
			enemiesLeft++;
		}

		objects[i]->Render(_window, scale);
	}
	for (int i = 0; i < birds.size(); ++i)
	{

		birds[i]->Render(_window, scale);

		if (birds[i]->PoofIndex == 0)
		{
			birdsLeft++;
		}
		else if (birds[i] == launchedBird)
		{
			launchedBird = nullptr;
		}
	}

	catapult->Render(_window);

	if (menu == -1)
	{
		if (enemiesLeft == 0)
		{
			menu = 3;
		}

		if (birdsLeft == 0)
		{
			menu = 2;
		}
	}
}

void Scene::Update()
{
	world->Step(1 / 60.f, 8, 3);
}

void Scene::Create(int sceneRequested)
{
	if (menu == 0)
	{
		menu = -1;

		objects.push_back(new Object(sf::Vector2f(480, 500), scale, b2BodyType::b2_staticBody, "Ground.png", world, &mFixtureUserData, 0));

		if (sceneRequested == 1)
		{
			objects.push_back(new Object(sf::Vector2f(585, 460), scale, b2BodyType::b2_dynamicBody, "Obstacles/Glass.png", world, &mFixtureUserData, 0, 1));
			objects.push_back(new Object(sf::Vector2f(775, 460), scale, b2BodyType::b2_dynamicBody, "Obstacles/Glass.png", world, &mFixtureUserData, 0, 1));
			objects.push_back(new Object(sf::Vector2f(680, 400), scale, b2BodyType::b2_dynamicBody, "Obstacles/LongPlank.png", world, &mFixtureUserData, 0, 10));

			objects.push_back(new Object(sf::Vector2f(670, 370), scale, b2BodyType::b2_dynamicBody, "Characters/AngryBird.png", world, &mFixtureUserData, -1));

			objects.push_back(new Object(sf::Vector2f(585, 360), scale, b2BodyType::b2_dynamicBody, "Obstacles/Box.png", world, &mFixtureUserData, 0, 10));
			objects.push_back(new Object(sf::Vector2f(775, 360), scale, b2BodyType::b2_dynamicBody, "Obstacles/Stone.png", world, &mFixtureUserData, 0, 20));
			objects.push_back(new Object(sf::Vector2f(585, 290), scale, b2BodyType::b2_dynamicBody, "Obstacles/Box.png", world, &mFixtureUserData, 0, 10));
			objects.push_back(new Object(sf::Vector2f(775, 290), scale, b2BodyType::b2_dynamicBody, "Obstacles/Box.png", world, &mFixtureUserData, 0, 10));
			objects.push_back(new Object(sf::Vector2f(680, 250), scale, b2BodyType::b2_dynamicBody, "Obstacles/LongPlank.png", world, &mFixtureUserData, 0, 10));

			objects.push_back(new Object(sf::Vector2f(620, 200), scale, b2BodyType::b2_dynamicBody, "Characters/AngryBird.png", world, &mFixtureUserData, -1));
			objects.push_back(new Object(sf::Vector2f(750, 200), scale, b2BodyType::b2_dynamicBody, "Characters/AngryBird.png", world, &mFixtureUserData, -1));

			AddQueue(1);
			AddQueue(1);
			AddQueue(2);

			Background = sf::Color(97, 136, 235);
		}

		if (sceneRequested == 2)
		{
			objects.push_back(new Object(sf::Vector2f(585, 460), scale, b2BodyType::b2_dynamicBody, "Obstacles/Glass.png", world, &mFixtureUserData, 0, 1));
			objects.push_back(new Object(sf::Vector2f(775, 460), scale, b2BodyType::b2_dynamicBody, "Obstacles/Glass.png", world, &mFixtureUserData, 0, 1));
			objects.push_back(new Object(sf::Vector2f(680, 400), scale, b2BodyType::b2_dynamicBody, "Obstacles/LongPlank.png", world, &mFixtureUserData, 0, 10));

			objects.push_back(new Object(sf::Vector2f(670, 370), scale, b2BodyType::b2_dynamicBody, "Characters/AngryBird.png", world, &mFixtureUserData, -1));

			objects.push_back(new Object(sf::Vector2f(585, 360), scale, b2BodyType::b2_dynamicBody, "Obstacles/Box.png", world, &mFixtureUserData, 0, 10));
			objects.push_back(new Object(sf::Vector2f(775, 360), scale, b2BodyType::b2_dynamicBody, "Obstacles/Stone.png", world, &mFixtureUserData, 0, 20));
			objects.push_back(new Object(sf::Vector2f(585, 290), scale, b2BodyType::b2_dynamicBody, "Obstacles/Box.png", world, &mFixtureUserData, 0, 10));
			objects.push_back(new Object(sf::Vector2f(775, 290), scale, b2BodyType::b2_dynamicBody, "Obstacles/Box.png", world, &mFixtureUserData, 0, 10));
			objects.push_back(new Object(sf::Vector2f(680, 250), scale, b2BodyType::b2_dynamicBody, "Obstacles/LongPlank.png", world, &mFixtureUserData, 0, 10));

			objects.push_back(new Object(sf::Vector2f(620, 200), scale, b2BodyType::b2_dynamicBody, "Characters/AngryBird.png", world, &mFixtureUserData, -1));
			objects.push_back(new Object(sf::Vector2f(750, 200), scale, b2BodyType::b2_dynamicBody, "Characters/AngryBird.png", world, &mFixtureUserData, -1));

			objects.push_back(new Object(sf::Vector2f(460, 370), scale, b2BodyType::b2_dynamicBody, "Characters/AngryBird.png", world, &mFixtureUserData, -1));

			objects.push_back(new Object(sf::Vector2f(450, 400), scale, b2BodyType::b2_dynamicBody, "Obstacles/Wagon.png", world, &mFixtureUserData, 0, 10));
			objects.push_back(new Object(sf::Vector2f(380, 410), scale, b2BodyType::b2_dynamicBody, "Obstacles/Wheel.png", world, &mFixtureUserData, 0, 10));
			objects.push_back(new Object(sf::Vector2f(600, 410), scale, b2BodyType::b2_dynamicBody, "Obstacles/Wheel.png", world, &mFixtureUserData, 0, 10));

			Joint joint(objects[objects.size() - 3], objects[objects.size() - 2], b2Vec2(-2.0f, 1.0f), world);
			Joint jointTwo(objects[objects.size() - 3], objects[objects.size() - 1], b2Vec2(2.0f, 1.0f), world);


			AddQueue(1);
			AddQueue(2);
			AddQueue(3);
			AddQueue(3);

			Background = sf::Color(235, 136, 97);
		}

		if (sceneRequested == 3)
		{
			objects.push_back(new Object(sf::Vector2f(585, 460), scale, b2BodyType::b2_dynamicBody, "Obstacles/Glass.png", world, &mFixtureUserData, 0, 1));
			objects.push_back(new Object(sf::Vector2f(775, 460), scale, b2BodyType::b2_dynamicBody, "Obstacles/Glass.png", world, &mFixtureUserData, 0, 1));
			objects.push_back(new Object(sf::Vector2f(680, 400), scale, b2BodyType::b2_dynamicBody, "Obstacles/LongPlank.png", world, &mFixtureUserData, 0, 10));

			objects.push_back(new Object(sf::Vector2f(670, 370), scale, b2BodyType::b2_dynamicBody, "Characters/AngryBird.png", world, &mFixtureUserData, -1));

			objects.push_back(new Object(sf::Vector2f(585, 360), scale, b2BodyType::b2_dynamicBody, "Obstacles/Box.png", world, &mFixtureUserData, 0, 10));
			objects.push_back(new Object(sf::Vector2f(775, 360), scale, b2BodyType::b2_dynamicBody, "Obstacles/Stone.png", world, &mFixtureUserData, 0, 20));
			objects.push_back(new Object(sf::Vector2f(585, 290), scale, b2BodyType::b2_dynamicBody, "Obstacles/Box.png", world, &mFixtureUserData, 0, 10));
			objects.push_back(new Object(sf::Vector2f(775, 290), scale, b2BodyType::b2_dynamicBody, "Obstacles/Box.png", world, &mFixtureUserData, 0, 10));
			objects.push_back(new Object(sf::Vector2f(680, 250), scale, b2BodyType::b2_dynamicBody, "Obstacles/LongPlank.png", world, &mFixtureUserData, 0, 10));

			objects.push_back(new Object(sf::Vector2f(620, 200), scale, b2BodyType::b2_dynamicBody, "Characters/AngryBird.png", world, &mFixtureUserData, -1));
			objects.push_back(new Object(sf::Vector2f(750, 200), scale, b2BodyType::b2_dynamicBody, "Characters/AngryBird.png", world, &mFixtureUserData, -1));

			AddQueue(3);
			AddQueue(2);
			AddQueue(2);
			AddQueue(1);
			AddQueue(3);

			Background = sf::Color(97, 0, 136);
		}
	}
}

void Scene::MouseButtonPressed(sf::RenderWindow& _window)
{
	if (menu == -1)
	{
		if (launchedBird != nullptr)
		{
			if (launchedBird->CharacterType == 2)
			{
				sf::Vector2f position = launchedBird->sprite.getPosition();

				launchedBird->sprite.setScale(.5f, .5f);
				//launchedBird->CreatePhysics(position, 15, b2BodyType::b2_dynamicBody, NULL);
				//launchedBird->sprite.setScale(launchedBird->sprite.getScale().x * 0.5f, launchedBird->sprite.getScale().x * 0.5f);
			//	launchedBird->shape.SetAsBox(launchedBird->sprite.getOrigin().x * .1f, launchedBird->sprite.getOrigin().y * .1f);
				//launchedBird->
				//launchedBird->bodyDef.position = b2Vec2(launchedBird->bodyDef.position.x / launchedBird->sprite.getScale().x, launchedBird->bodyDef.position.y / launchedBird->sprite.getScale().x);

				for (int i = 0; i < 2; i++)
				{

					Bird* bird = NewBird(new Bird(launchedBird->CharacterType), _window);
					//bird->SetScale(bird->sprite.getScale().x * 0.5f);
					bird->sprite.setScale(.5f, .5f);
					birds.push_back(bird);

					position.y -= i * 10;
					bird->sprite.setPosition(position);

					catapult->LaunchBird(scale, *world);
				}
				launchedBird = nullptr;
				return;
			}

			if (launchedBird->CharacterType == 3)
			{
				catapult->ImpulseBody(launchedBird->body, 8);
				launchedBird = nullptr;
				return;
			}
		}

		GetQueue(_window);
	}

}

void Scene::MouseButtonReleased(sf::RenderWindow& _window)
{
	if (catapult->loadedBird != nullptr)
	{
		launchedBird = catapult->loadedBird;
		objects.push_back(launchedBird);
		catapult->LaunchBird(scale, *world);
	}
}

void Scene::GetQueue(sf::RenderWindow& _window)
{
	//birds.push_back(new Bird(1));
	for (int i = 0; i < birds.size(); i++)
	{
		if (birds[i]->waiting)
		{
			birds[i]->waiting = false;
			NewBird(birds[i], _window);
			break;
		}
	}
}

Bird* Scene::NewBird(Bird* bird, sf::RenderWindow& _window)
{
	bird->listener.mFixtureUserData = &mFixtureUserData;
	catapult->LoadBird(bird);
	catapult->MoveBird(_window);

	return bird;
}

void Scene::End()
{
	objects.clear();
	birds.clear();
	mFixtureUserData.clear();
	launchedBird = nullptr;
	menu = 0;

	delete world;
	delete catapult;
	Initialise();
}

void Scene::AddQueue(int type)
{
	birds.push_back(new Bird(type, true));
	birds[birds.size() - 1]->sprite.setPosition(sf::Vector2f(200 - birds.size() * 35, 450));
}

void Scene::MouseMoved(sf::RenderWindow& _window)
{
	catapult->MoveBird(_window);
}
