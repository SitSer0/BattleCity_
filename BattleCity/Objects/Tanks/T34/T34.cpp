
#include "T34.h"

T34::T34(SDL_Renderer *renderer, Position position, Direction direction)
    : Tank(renderer, position, sizeTank, direction, T34Health, T34Speed,
           imgT34){};
