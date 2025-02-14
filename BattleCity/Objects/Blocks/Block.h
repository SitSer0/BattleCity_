
#include "../Object.h"

#ifndef BATTLECITY__BLOCK_H_
#define BATTLECITY__BLOCK_H_

class Block : public Object {
 public:
  Block(SDL_Renderer* renderer, Position position, Size size,
        Direction direction, const std::map<Direction, std::string>& imagePath)
      : Object(renderer, position, size, direction, imagePath) {}

  virtual std::string type() const { return "Block"; }

  void update() override {
  }
};

#endif  // BATTLECITY__BLOCK_H_