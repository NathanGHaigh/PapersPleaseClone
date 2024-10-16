
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
	in_menu = true;
	gameplay = false;
	win_menu = false;
  character = new sf::Sprite;
  passport = new sf::Sprite;
  accept_stamp = new sf::Sprite;
  reject_stamp = new sf::Sprite;
  accept_stamp_passport = new sf::Sprite;
  reject_stamp_passport = new sf::Sprite;

  stamped = false;
  passport_accepted = false;
  passport_rejected = false;
  quota = 10;

  std::cout << "Starting" << std::endl;
  //_____________________________________________________________________________________________
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
  //_______________________________________________________________________________________________
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
  //_______________________________________________________________________________________________
  //Loading Stamp Textures, Setting Stamps and Setting Button Positions
  if (!stamps[0].loadFromFile("../Data/Images/Critter Crossing Customs/accept button.png"))
  {
	  
	  std::cout << "Texture stamp[0] didn't load in \n";
  }

  if (!stamps[1].loadFromFile("../Data/Images/Critter Crossing Customs/reject button.png"))
  {
	  
	  std::cout << "Texture stamp[1] didn't load in \n";
  }

  if (!stamps[2].loadFromFile("../Data/Images/Critter Crossing Customs/accept.png"))
  {

	  std::cout << "Texture stamp[1] didn't load in \n";
  }

  if (!stamps[3].loadFromFile("../Data/Images/Critter Crossing Customs/reject.png"))
  {

	  std::cout << "Texture stamp[1] didn't load in \n";
  }

  accept_stamp->setTexture(stamps[0]);
  accept_stamp->setPosition(1620, 820);

  reject_stamp->setTexture(stamps[1]);
  reject_stamp->setPosition(1620, 930);

  accept_stamp_passport->setTexture(stamps[2]);

  reject_stamp_passport->setTexture(stamps[3]);
  reject_stamp_passport->setScale(0.8, 0.8);
  //________________________________________________________________________________________________________
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
  //_______________________________________________________________________________________________________
  //Text Set Up
  if (!font.loadFromFile("../Data/Fonts/OpenSans-Bold.ttf"))
  {
	  std::cout << "Font didn't load in \n";
  }

  
  title_text.setString("Animal Crossing: Legal Edition");
  title_text.setFont(font);
  title_text.setCharacterSize(100);
  title_text.setFillColor(sf::Color(255, 255, 255, 255));
  title_text.setPosition(window.getSize().x / 2 - title_text.getGlobalBounds().width / 2,
	  window.getSize().y / 3.5 - title_text.getGlobalBounds().height / 3.5);

  play_text.setString("Press Enter to Play");
  play_text.setFont(font);
  play_text.setCharacterSize(50);
  play_text.setFillColor(sf::Color(255, 255, 255, 255));
  play_text.setPosition(window.getSize().x / 2 - play_text.getGlobalBounds().width / 2,
	  window.getSize().y / 1.5 - play_text.getGlobalBounds().height / 3.5);

  win_text.setString("Quota Met, You are a great great Asset to the Border Control");
  win_text.setFont(font);
  win_text.setCharacterSize(60);
  win_text.setFillColor(sf::Color(255, 255, 255, 255));
  win_text.setPosition(window.getSize().x / 2 - win_text.getGlobalBounds().width / 2,
	  window.getSize().y / 3.5 - win_text.getGlobalBounds().height / 3.5);

  quit_text.setString("Press Q to Quit");
  quit_text.setFont(font);
  quit_text.setCharacterSize(50);
  quit_text.setFillColor(sf::Color(255, 255, 255, 255));
  quit_text.setPosition(window.getSize().x / 2 - quit_text.getGlobalBounds().width / 2,
	  window.getSize().y / 1.5 - quit_text.getGlobalBounds().height / 3.5);

  quota_text.setString("Quota:" + std::to_string(quota_counter) + "/" + std::to_string(quota));
  quota_text.setFont(font);
  quota_text.setCharacterSize(25);
  quota_text.setFillColor(sf::Color(0, 0, 0, 255));
  quota_text.setPosition(30, 15);

  lives_text.setString("Lives:" + std::to_string(lives));
  lives_text.setFont(font);
  lives_text.setCharacterSize(25);
  lives_text.setFillColor(sf::Color(0, 0, 0, 255));
  lives_text.setPosition(1800, 15);

  newAnimal();
  return true;
}

void Game::update(float dt)
{
	if (gameplay)
	{
		dragSprite(dragged);
		accept_stamp_passport->setPosition(passport->getPosition().x + passport->getGlobalBounds().width / 7, passport->getPosition().y + passport->getGlobalBounds().height / 8);
		reject_stamp_passport->setPosition(passport->getPosition().x + passport->getGlobalBounds().width / 7, passport->getPosition().y + passport->getGlobalBounds().height / 8);

		if (passport->getPosition().x <= 100 && passport->getPosition().y <= 100 && stamped == true)
		{
			std::cout << "Passport Returned \n";
			if (should_accept == true && passport_accepted == true)
			{
				std::cout << "Correct\n";
				quota_counter += 1;
				std::cout << quota_counter << std::endl;
				scoreCounter(quota_counter);
				newAnimal();

			}
			else if (should_accept == false && passport_rejected == true)
			{
				std::cout << "Correct\n";
				quota_counter += 1;
				std::cout << quota_counter << std::endl;
				scoreCounter(quota_counter);
				newAnimal();
			}
			else
			{
				std::cout << "Wrong\n";
				lives -= 1;
				livesCounter(lives);
				std::cout << lives << std::endl;
				newAnimal();

			}
		}
	}
}

void Game::render()
{
	if (in_menu)
	{
		window.draw(title_text);
		window.draw(play_text);
	}
	if (gameplay)
	{
		window.draw(background);
		window.draw(*character);
		window.draw(*passport);
		window.draw(quota_text);
		window.draw(lives_text);

		if (passport_accepted)
		{
			window.draw(*accept_stamp_passport);
		}

		if (passport_rejected)
		{
			window.draw(*reject_stamp_passport);
		}

		if (is_active)
		{
			window.draw(*accept_stamp);
			window.draw(*reject_stamp);
		}
	}
	if (win_menu)
	{
		window.draw(win_text);
		window.draw(quit_text);
	}
}

void Game::mouseClicked(sf::Event event)
{
  //get the click position
  sf::Vector2i click = sf::Mouse::getPosition(window);


}

void Game::keyPressed(sf::Event event)
{
	if (event.key.code == sf::Keyboard::Q)
	{
		window.close();
	}
	if (in_menu)
	{
		if (event.key.code == sf::Keyboard::Enter)
		{
			in_menu = false;
			gameplay = true;
		}
	}
}

void Game::newAnimal()
{
	dragged = nullptr;
	stamped = false;
	passport_accepted = false;
	passport_rejected = false;

	int animal_index = rand() % 3;
	int passport_index = rand() % 3;

	if (animal_index == passport_index)
	{
		should_accept = true;
		std::cout << "Should Accept \n";

	}
	else
	{
		should_accept = false;
		std::cout << "Should Reject \n";
	}

	character->setTexture(animals[animal_index], true);
	character->setScale(1.8, 1.8);
	character->setPosition(window.getSize().x / 10, window.getSize().y / 12);

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

		if (accept_stamp->getGlobalBounds().contains(clickf) && is_active)
		{
			std::cout << "Accept Button Clicked" << std::endl;
			stamped = true;
			passport_accepted = true;
			passport_rejected = false;
		}

		if (reject_stamp->getGlobalBounds().contains(clickf) && is_active)
		{
			std::cout << "Reject Button Clicked" << std::endl;
			stamped = true;
			passport_accepted = false;
			passport_rejected = true;
		}
	}

	if (event.mouseButton.button == sf::Mouse::Right)
	{
		sf::Vector2i click = sf::Mouse::getPosition(window);
		sf::Vector2f clickf = static_cast<sf::Vector2f>(click);

		if (passport->getGlobalBounds().contains(clickf))
		{
			std::cout << "Stamp Choice" << std::endl;
			is_active = true;
		}
		else
		{
			is_active = false;
		}
	}
}

void Game::mouseButtonReleased(sf::Event event)
{
	dragged = nullptr;
}

void Game::scoreCounter(int quota_counter)
{
	quota_text.setString("Quota:" + std::to_string(quota_counter) + "/" + std::to_string(quota));
	if (quota_counter == quota)
	{
		std::cout << "You Win" << std::endl;
		win_menu = true;
		gameplay = false;
	}
}

void Game::livesCounter(int lives)
{
	lives_text.setString("Lives:" + std::to_string(lives));
	if (lives == 0)
	{
		std::cout << "You Lose" << std::endl;
		quota_counter = 0;
		lives = 3;
		lives_text.setString("Lives:" + std::to_string(lives));
		gameplay = false;
		in_menu = true;
	}
}

