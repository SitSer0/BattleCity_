

#ifndef BATTLECITY_OBJECTS_TANKS_MOUSE_MOUSE_H_
#define BATTLECITY_OBJECTS_TANKS_MOUSE_MOUSE_H_

#include "../Tank.h"

class Mouse : public Tank {
 public:
  Mouse(SDL_Renderer* renderer, Position position, Direction direction);

  std::string type() const override { return "Mouse"; }
};

#endif  // BATTLECITY_OBJECTS_TANKS_MOUSE_MOUSE_H_
