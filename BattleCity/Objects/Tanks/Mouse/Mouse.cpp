
#include "Mouse.h"

Mouse::Mouse(SDL_Renderer *renderer, Position position, Direction direction)
    : Tank(renderer, position, sizeTank, direction, MouseHealth, MouseSpeed,
           imgMouse) {}
