// Класс определяет взаимодействие предметов на игровом поле.
// Object -> Bullet
//
//        -> Block -> Stone
//                 -> BrickWall
//                 -> Bushes
//
//        -> Tank  -> T34 (тип танка основного(-ых) игрока(-ов))
//                 -> Tiger (обычный танк, по характеристикам такой же как и у игроков)
//                 -> Panther (увеличенная скорость)
//                 -> Mouse (увеличенное здоровье)

#ifndef BATTLECITY__OBJECT_H_
#define BATTLECITY__OBJECT_H_

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>

#include "../constatnti_itd.h"

class Object {
 public:
  Object(SDL_Renderer* renderer, Position position, Size size, Direction direction, const std::map<Direction, std::string>& imagePath)
      : renderer(renderer), position(position), size(size), direction(direction), imagePath(imagePath) {
    updateTexture(); // Загружаем начальную текстуру
  }

  virtual ~Object() {
    if (texture != nullptr) {
      SDL_DestroyTexture(texture);
    }
  }

  void Draw() const;
  virtual void update() {};

  virtual std::string type() const ;

  bool isTouch(Object* other);
  Position getPosition() {
    return position;
  }
  Size getSize() {
    return size;
  }

  void updateTexture();

 protected:

  SDL_Renderer* renderer;
  Position position;
  Size size;
  Direction direction;
  std::map<Direction, std::string> imagePath;
  SDL_Texture* texture = nullptr;


};

#endif //BATTLECITY__OBJECT_H_
