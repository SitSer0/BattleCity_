//
// Created by Serafim on 05.04.2024.
//

#include "Base.h"

Base::Base(SDL_Renderer *renderer, Position position)
    : Object(renderer, position, sizeBase, Direction::UP, imgBase) {}
