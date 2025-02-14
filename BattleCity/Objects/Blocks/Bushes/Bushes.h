#ifndef BATTLECITY__BUSHES_H_
#define BATTLECITY__BUSHES_H_


#include "../Block.h"

class Bushes : public Block {
 public:
  Bushes(SDL_Renderer* renderer, Position position, Size size = sizeBlock,
         Direction direction = Direction::UP, const std::map<Direction, std::string>& imagePath = imgBushes)
      : Block(renderer, position, size, direction, imagePath) {}
  std::string type() const override { return "Bushes"; }


};

#endif  // BATTLECITY__BUSHES_H_
