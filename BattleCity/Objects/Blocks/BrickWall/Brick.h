//
// Created by Serafim on 15.03.2024.
//

#ifndef BATTLECITY__BRICK_H_
#define BATTLECITY__BRICK_H_

#include "../Block.h"

class Brick : public Block {
 public:
  // Используем конструктор базового класса
  Brick(SDL_Renderer* renderer, Position position, Size size = sizeBlock,
        Direction direction = Direction::UP, const std::map<Direction, std::string>& imagePath = imgBrickWall)
      : Block(renderer, position, size, direction, imagePath) {}
  std::string type() const override { return "Brick"; }


};

#endif  // BATTLECITY__BRICK_H_
