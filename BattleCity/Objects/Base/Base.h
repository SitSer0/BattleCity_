//
// Created by Serafim on 05.04.2024.
//

#ifndef BATTLECITY_OBJECTS_BASE_BASE_H_
#define BATTLECITY_OBJECTS_BASE_BASE_H_

#include "../Object.h"

class Base : public Object {
 public:
  Base(SDL_Renderer* renderer, Position position);
 protected:
  std::string type() const override { return "Bullet"; }
};

#endif  // BATTLECITY_OBJECTS_BASE_BASE_H_
