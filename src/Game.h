
#ifndef PLATFORMER_GAME_H
#define PLATFORMER_GAME_H

#include <SFML/Graphics.hpp>

class Game
{
 public:
  Game(sf::RenderWindow& window);
  ~Game();
  bool init();
  void update(float dt);
  void render();
  void mouseClicked(sf::Event event);
  void keyPressed(sf::Event event);
  void mouseButtonPressed(sf::Event event);
  void mouseButtonReleased(sf::Event event);


  void newAnimal();
  void dragSprite(sf::Sprite* sprite);

 private:
  sf::RenderWindow& window;

  sf::Sprite* character;
  sf::Sprite* passport;

  sf::Sprite* dragged = nullptr;
  sf::Vector2f drag_offset;

  sf::Texture* animals = new sf::Texture[3];
  sf::Texture* passports = new sf::Texture[3];

  sf::Sprite background;
  sf::Texture background_texture;

  bool should_accept;
  bool passport_accepted;
  bool passport_rejected;

};

#endif // PLATFORMER_GAME_H
