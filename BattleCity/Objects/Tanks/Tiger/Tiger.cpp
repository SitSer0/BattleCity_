
#include "Tiger.h"

Tiger::Tiger(SDL_Renderer *renderer, Position position, Direction direction)
    : Tank(renderer, position, sizeTank, direction, TigerHealth, TigerSpeed,
           imgTiger){};
