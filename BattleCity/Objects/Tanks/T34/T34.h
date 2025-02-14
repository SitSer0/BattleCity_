

#ifndef BATTLECITY_OBJECTS_TANKS_T34_T34_H_
#define BATTLECITY_OBJECTS_TANKS_T34_T34_H_

#include "../Tank.h"

class T34 : public Tank {
 public:
  T34(SDL_Renderer* renderer, Position position, Direction direction);

  std::string type() const override { return "T34"; }
};

#endif  // BATTLECITY_OBJECTS_TANKS_T34_T34_H_
