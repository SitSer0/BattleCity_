//
// Created by Serafim on 14.03.2024.
//

#ifndef BATTLECITY__CONSTATNTI_ITD_H_
#define BATTLECITY__CONSTATNTI_ITD_H_

#include <map>
#include <vector>

enum class Direction { UP, DOWN, LEFT, RIGHT };

struct Position {
  int x;
  int y;
  Position(int pos_x, int pos_y) {
    x = pos_x;
    y = pos_y;
  }
  bool operator==(const Position& other) const {
    return (x == other.x) && (y == other.y);
  }
  bool operator!=(const Position& other) const {
    return !(*this == other);
  }
};

struct Size {
  int sizeX;
  int sizeY;
  Size(int newSizeX, int newSizeY) {
    sizeX = newSizeX;
    sizeY = newSizeY;
  }
};

const int GAME_WEIGHT = 1300;
const int GAME_HEIGHT = 830;

const int T34Health = 10;
const int TigerHealth = 10;
const int PantherHealth = 10;
const int MouseHealth = 40;

const int T34Speed = 7;
const int TigerSpeed = 2;
const int PantherSpeed = 3;
const int MouseSpeed = 1;

const int bulletSpeed = 5;

const int bulletDamage = 10;

const Size sizeTank = Size(45, 45);
const Size sizeBullet = Size(12, 12);
const Size sizeBlock = Size(30, 30);
const Size sizeBase = Size(60, 60);

const std::map<Direction, std::string> imgObject;

const std::map<Direction, std::string> imgT34 = {
    {Direction::LEFT, "../Objects/Tanks/T34/t34_left.png"},
    {Direction::RIGHT, "../Objects/Tanks/T34/t34_right.png"},
    {Direction::UP, "../Objects/Tanks/T34/t34_up.png"},
    {Direction::DOWN, "../Objects/Tanks/T34/t34_down.png"}};

const std::map<Direction, std::string> imgTiger = {
    {Direction::LEFT, "../Objects/Tanks/Tiger/tiger_left.png"},
    {Direction::RIGHT, "../Objects/Tanks/Tiger/tiger_right.png"},
    {Direction::UP, "../Objects/Tanks/Tiger/tiger_up.png"},
    {Direction::DOWN, "../Objects/Tanks/Tiger/tiger_down.png"}};

const std::map<Direction, std::string> imgPanther = {
    {Direction::LEFT, "../Objects/Tanks/Panther/panther_left.png"},
    {Direction::RIGHT, "../Objects/Tanks/Panther/panther_right.png"},
    {Direction::UP, "../Objects/Tanks/Panther/panther_up.png"},
    {Direction::DOWN, "../Objects/Tanks/Panther/panther_down.png"}};

const std::map<Direction, std::string> imgMouse = {
    {Direction::LEFT, "../Objects/Tanks/Mouse/mouse_left.png"},
    {Direction::RIGHT, "../Objects/Tanks/Mouse/mouse_right.png"},
    {Direction::UP, "../Objects/Tanks/Mouse/mouse_up.png"},
    {Direction::DOWN, "../Objects/Tanks/Mouse/mouse_down.png"}};

const std::map<Direction, std::string> imgBrickWall = {
    {Direction::LEFT, "../Objects/Blocks/BrickWall/brick_wall.png"},
    {Direction::RIGHT, "../Objects/Blocks/BrickWall/brick_wall.png"},
    {Direction::UP, "../Objects/Blocks/BrickWall/brick_wall.png"},
    {Direction::DOWN, "../Objects/Blocks/BrickWall/brick_wall.png"}};

const std::map<Direction, std::string> imgBushes = {
    {Direction::LEFT, "../Objects/Blocks/Bushes/bushes.png"},
    {Direction::RIGHT, "../Objects/Blocks/Bushes/bushes.png"},
    {Direction::UP, "../Objects/Blocks/Bushes/bushes.png"},
    {Direction::DOWN, "../Objects/Blocks/Bushes/bushes.png"}};

const std::map<Direction, std::string> imgStone = {
    {Direction::LEFT, "../Objects/Blocks/Stone/stone.png"},
    {Direction::RIGHT, "../Objects/Blocks/Stone/stone.png"},
    {Direction::UP, "../Objects/Blocks/Stone/stone.png"},
    {Direction::DOWN, "../Objects/Blocks/Stone/stone.png"}};

const std::map<Direction, std::string> imgBullet = {
    {Direction::LEFT, "../Objects/Bullets/bullet_left.png"},
    {Direction::RIGHT, "../Objects/Bullets/bullet_right.png"},
    {Direction::UP, "../Objects/Bullets/bullet_up.png"},
    {Direction::DOWN, "../Objects/Bullets/bullet_down.png"}};

const std::map<Direction, std::string> imgBase = {{Direction::LEFT, "path"},
                                                  {Direction::RIGHT, "path"},
                                                  {Direction::UP, "path"},
                                                  {Direction::DOWN, "path"}};

const std::vector<Position> BadCells = {
    Position(11, 24),
    Position(14, 24),
    Position(11, 23),
    Position(14, 23),
    Position(11, 22),
    Position(12, 22),
    Position(13, 22),
    Position(14, 22)
};

const std::vector<Position> EnemySpawnPositions = {
    Position(3, 3)
};
const std::vector<Position> PlayersSpawnPositions = {};

#endif  // BATTLECITY__CONSTATNTI_ITD_H_