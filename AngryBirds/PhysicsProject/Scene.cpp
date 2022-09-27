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
	int enemies = 0;

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

		if (objects[i]->isEnemy)
		{
			enemies++;
		}

		objects[i]->Render(_window, scale);
	}
	for (int i = 0; i < birds.size(); ++i)
	{
		birds[i]->Render(_window, scale);
	}

	catapult->Render(_window);

	if (enemies == 0)
	{
		End();

	}
}

void Scene::Update()
{
	world->Step(1 / 60.f, 8, 3);
}

void Scene::Create(int scene)
{
	if (status == 0)
	{
		status = 1;

		objects.push_back(new Object(sf::Vector2f(480, 500), scale, b2BodyType::b2_staticBody, "Ground.png", world, &mFixtureUserData));

		if (scene == 1)
		{
			for (int i = 0; i < 3; ++i)
			{
				objects.push_back(new Object(sf::Vector2f(550 + i * 100, 400), scale, b2BodyType::b2_dynamicBody, "Characters/AngryBird.png", world, &mFixtureUserData, true));
			}

			objects.push_back(new Object(sf::Vector2f(450, 400), scale, b2BodyType::b2_dynamicBody, "Obstacles/Wagon.png", world, &mFixtureUserData));
			objects.push_back(new Object(sf::Vector2f(380, 410), scale, b2BodyType::b2_dynamicBody, "Obstacles/Wheel.png", world, &mFixtureUserData));
			objects.push_back(new Object(sf::Vector2f(600, 410), scale, b2BodyType::b2_dynamicBody, "Obstacles/Wheel.png", world, &mFixtureUserData));

			Joint joint(objects[objects.size() - 3], objects[objects.size() - 2], b2Vec2(-2.0f, 1.0f), world);
			Joint jointTwo(objects[objects.size() - 3], objects[objects.size() - 1], b2Vec2(2.0f, 1.0f), world);


			AddQueue(1);
			AddQueue(1);
			AddQueue(2);

			Background = sf::Color(97, 136, 235);
		}

		if (scene == 2)
		{
			for (int i = 0; i < 5; ++i)
			{
				objects.push_back(new Object(sf::Vector2f(350 + i * 80, 400), scale, b2BodyType::b2_dynamicBody, "Characters/AngryBird.png", world, &mFixtureUserData, true));
			}

			/*
			objects.push_back(new Object(sf::Vector2f(450, 400), scale, b2BodyType::b2_dynamicBody, "Wagon.png", world, &mFixtureUserData));
			objects.push_back(new Object(sf::Vector2f(380, 410), scale, b2BodyType::b2_dynamicBody, "Wheel.png", world, &mFixtureUserData));
			objects.push_back(new Object(sf::Vector2f(600, 410), scale, b2BodyType::b2_dynamicBody, "Wheel.png", world, &mFixtureUserData));

			Joint joint(objects[objects.size() - 3], objects[objects.size() - 2], b2Vec2(-2.0f, 1.0f), world);
			Joint jointTwo(objects[objects.size() - 3], objects[objects.size() - 1], b2Vec2(2.0f, 1.0f), world);
			*/


			AddQueue(1);
			AddQueue(2);
			AddQueue(3);
			AddQueue(3);

			Background = sf::Color(235, 136, 97);
		}

		if (scene == 3)
		{
			for (int i = 0; i < 7; ++i)
			{
				objects.push_back(new Object(sf::Vector2f(350 + i * 65, 400), scale, b2BodyType::b2_dynamicBody, "Characters/AngryBird.png", world, &mFixtureUserData, true));
			}

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
	if (launchedBird != nullptr)
	{
		if (launchedBird->type == 2)
		{
			sf::Vector2f position = launchedBird->sprite.getPosition();
			for (int i = 0; i < 2; i++)
			{

				Bird* bird = NewBird(new Bird(launchedBird->type), _window);
				birds.push_back(bird);

				position.y -= i * 10;
				bird->sprite.setPosition(position);

				catapult->LaunchBird(30.0f, *world);
			}
			launchedBird = nullptr;
			return;
		}

		if (launchedBird->type == 3)
		{
			catapult->ImpulseBody(launchedBird->body, 8);
			launchedBird = nullptr;
			return;
		}
	}

	GetQueue(_window);

}

void Scene::MouseButtonReleased(sf::RenderWindow& _window)
{
	if (catapult->loadedBird != nullptr)
	{
		launchedBird = catapult->loadedBird;

		catapult->LaunchBird(30.0f, *world);
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
	sceneNumber = 0;
	status = 0;

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
