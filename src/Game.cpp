
#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow& game_window)
  : window(game_window)
{
  srand(time(NULL));
}

Game::~Game()
{
	delete [] animals;
	delete[] passports;
	delete character;
	delete passport;
}

bool Game::init()
{
  character = new sf::Sprite;
  passport = new sf::Sprite;

  //Loading Animal Textures
  if (!animals[0].loadFromFile("../Data/Images/kenney_animalpackredux/PNG/Round/elephant.png"))
  {
	  std::cout << "Texture animals[0] didn't load in \n";
  }

  if (!animals[1].loadFromFile("../Data/Images/kenney_animalpackredux/PNG/Round/moose.png"))
  {
	  std::cout << "Texture animals[1] didn't load in \n";
  }

  if (!animals[2].loadFromFile("../Data/Images/kenney_animalpackredux/PNG/Round/penguin.png"))
  {
	  std::cout << " Texture animals[2] didn't load in \n";
  }
  
  //
  //Loading Passport Textures
  if (!passports[0].loadFromFile("../Data/Images/Critter Crossing Customs/elephant passport.png"))
  {
	  std::cout << "Texture passport[0] didn't load in \n";
  }

  if (!passports[1].loadFromFile("../Data/Images/Critter Crossing Customs/moose passport.png"))
  {
	  std::cout << "Texture passport[1] didn't load in \n";
  }

  if (!passports[2].loadFromFile("../Data/Images/Critter Crossing Customs/penguin passport.png"))
  {
	  std::cout << " Texture passport[2] didn't load in \n";
  }
  //
  //Loading Backgorund Textures
  if (!background_texture.loadFromFile("../Data/Images/kenney_physicspack/PNG/Backgrounds/blue_desert.png"))
  {
	  std::cout << "Background didn't load in \n";
  }
  background.setTexture(background_texture);

  //Background set up that scales to window width
  auto TextureSize = background_texture.getSize(); // Get size of
  // texture.
  const sf::Vector2u& WindowSize = window.getSize(); // Get size of window.

  float ScaleX = (float)WindowSize.x / float(TextureSize.x);
  float ScaleY = (float)WindowSize.y / float(TextureSize.y);     //Calculate scale.

  background.setTexture(background_texture);
  background.setScale(ScaleX, ScaleY);

  newAnimal();
  return true;
}

void Game::update(float dt)
{
	dragSprite(dragged);
}

void Game::render()
{
	window.draw(background);
	window.draw(*character);
	window.draw(*passport);
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);


}

void Game::keyPressed(sf::Event event)
{
	
}

void Game::newAnimal()
{
	passport_accepted = false;
	passport_rejected = false;

	int animal_index = rand() % 3;
	int passport_index = rand() % 3;

	if (animal_index == passport_index)
	{
		should_accept = true;
	}
	else
	{
		should_accept = false;
	}

	character->setTexture(animals[animal_index], true);
	character->setScale(1.8, 1.8);
	character->setPosition(window.getSize().x / 2, window.getSize().y / 12);

	passport->setTexture(passports[passport_index], true);
	passport->setScale(0.6, 0.6);
	passport->setPosition(window.getSize().x / 2, window.getSize().y / 3);
}

void Game::dragSprite(sf::Sprite* sprite)
{	
	if (sprite != nullptr)
	{
		sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
		sf::Vector2f mouse_positionf = static_cast<sf::Vector2f>(mouse_position);
		sf::Vector2f drag_position = mouse_positionf - drag_offset;
		sprite->setPosition(drag_position.x, drag_position.y);
	}
}

void Game::mouseButtonPressed(sf::Event event)
{
	if (event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i click = sf::Mouse::getPosition(window);
		sf::Vector2f clickf = static_cast<sf::Vector2f>(click);

		if (passport->getGlobalBounds().contains(clickf))
		{		
			
			drag_offset.x = sf::Mouse::getPosition(window).x - passport->getPosition().x;
			drag_offset.y = sf::Mouse::getPosition(window).y - passport->getPosition().y;

			dragged = passport;
		}
	}
}

void Game::mouseButtonReleased(sf::Event event)
{
	dragged = nullptr;
}


