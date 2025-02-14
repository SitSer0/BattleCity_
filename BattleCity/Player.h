//
// Created by Serafim on 03.04.2024.
//

#ifndef BATTLECITY__PLAYER_H_
#define BATTLECITY__PLAYER_H_

#include "Objects/Tanks/Tank.h"


class Player {
 private:
  int life_count;
  Tank* tank;
 public:
  void moveLeft();
  void moveRight();
  void moveUp();
  void moveDown();

  Tank* getTank();
  int getLifeCount();
};

#endif  // BATTLECITY__PLAYER_H_
