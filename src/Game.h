
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
  void scoreCounter(int quota_counter);


  void newAnimal();
  void dragSprite(sf::Sprite* sprite);

 private:
  sf::RenderWindow& window;

  sf::Sprite* character;
  sf::Sprite* passport;
  sf::Sprite* accept_stamp;
  sf::Sprite* reject_stamp;
  sf::Sprite* accept_stamp_passport;
  sf::Sprite* reject_stamp_passport;

  sf::Sprite* dragged = nullptr;
  sf::Vector2f drag_offset;

  sf::Texture* animals = new sf::Texture[3];
  sf::Texture* passports = new sf::Texture[3];
  sf::Texture* stamps = new sf::Texture[4];

  sf::Sprite background;
  sf::Texture background_texture;

  bool stamped;
  bool should_accept;
  bool passport_accepted;
  bool passport_rejected;
  bool is_active = false;

  int quota;
  int quota_counter = 0;
  int lives = 3;

};

#endif // PLATFORMER_GAME_H
