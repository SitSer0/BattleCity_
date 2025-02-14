

#ifndef BATTLECITY_OBJECTS_TANKS_TIGER_TIGER_H_
#define BATTLECITY_OBJECTS_TANKS_TIGER_TIGER_H_

#include "../Tank.h"

class Tiger : public Tank {
 public:
  Tiger(SDL_Renderer* renderer, Position position, Direction direction);

  std::string type() const override { return "Tiger"; }
};

#endif  // BATTLECITY_OBJECTS_TANKS_TIGER_TIGER_H_
