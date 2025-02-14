//
// Created by Serafim on 03.04.2024.
//

#include "Player.h"

void Player::moveRight() {
  tank->moveRight();
}

void Player::moveLeft() {
  tank->moveLeft();
}

void Player::moveDown() {
  tank->moveDown();
}

void Player::moveUp() {
  tank->moveUp();
}

Tank* Player::getTank() {
  return tank;
}

int Player::getLifeCount() {
  return life_count;
}