
#ifndef BATTLECITY_OBJECTS_TANKS_PANTHER_PANTHER_H_
#define BATTLECITY_OBJECTS_TANKS_PANTHER_PANTHER_H_

#include "../Tank.h"

class Panther : public Tank {
 public:
  Panther(SDL_Renderer* renderer, Position position, Direction direction);

  std::string type() const override { return "Panther"; }
};

#endif  // BATTLECITY_OBJECTS_TANKS_PANTHER_PANTHER_H_
