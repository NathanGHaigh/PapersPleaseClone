
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
  
  if (!background_texture.loadFromFile("Data/Images/kenney_physicspack/PNG/Backgrounds/colored_land.png"))
  {
	  std::cout << "Background didn't load in \n";
  }
  background.setTexture(background_texture);

  return true;
}

void Game::update(float dt)
{

}

void Game::render()
{
	window.draw(background);
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

	passport->setTexture(animals[animal_index], true);
	passport->setScale(0.6, 0.6);
	passport->setPosition(window.getSize().x / 2, window.getSize().y / 3);
}


