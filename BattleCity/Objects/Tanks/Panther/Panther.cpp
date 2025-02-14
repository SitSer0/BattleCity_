
#include "Panther.h"

Panther::Panther(SDL_Renderer *renderer, Position position, Direction direction)
    : Tank(renderer, position, sizeTank, direction, PantherHealth, PantherSpeed,
           imgPanther) {}
