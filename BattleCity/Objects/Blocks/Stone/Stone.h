//
// Created by Serafim on 15.03.2024.
//

#ifndef BATTLECITY__STONE_H_
#define BATTLECITY__STONE_H_

#include "../Block.h"

class Stone : public Block {
 public:
  Stone(SDL_Renderer* renderer, Position position, Size size = sizeBlock,
        Direction direction = Direction::UP, const std::map<Direction, std::string>& imagePath = imgStone)
      : Block(renderer, position, size, direction, imagePath) {}
  std::string type() const override { return "Stone"; }
};

#endif  // BATTLECITY__STONE_H_
