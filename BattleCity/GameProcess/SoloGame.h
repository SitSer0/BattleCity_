//
// Created by Serafim on 23.04.2024.
//

#ifndef BATTLECITY_GAMEPROCESS_SOLOGAME_H_
#define BATTLECITY_GAMEPROCESS_SOLOGAME_H_

#include <SDL.h>

#include <memory>
#include <vector>

#include "../Objects/Blocks/Block.h"
#include "../Objects/Blocks/BrickWall/Brick.h"
#include "../Objects/Blocks/Bushes/Bushes.h"
#include "../Objects/Blocks/Stone/Stone.h"
#include "../Objects/Bullets/Bullet.h"
#include "../Objects/Object.h"
#include "../Objects/Tanks/Mouse/Mouse.h"
#include "../Objects/Tanks/Panther/Panther.h"
#include "../Objects/Tanks/T34/T34.h"
#include "../Objects/Tanks/Tank.h"
#include "../Objects/Tanks/Tiger/Tiger.h"
#include "../Player.h"

class SoloGame {
 public:
  SoloGame(std::string fileName, SDL_Window* wind, SDL_Renderer* rend);

  bool Initialize();
  void RunLoop();
  void ShutDown();

  void generateOutput();
  void playerInput();
  void updateGame();
  void addNewTanks();
  void addStarterTanks();
  void addStarterBlocks();

  void addT34(Position pos);
  void addTiger(Position pos);
  void addPanther(Position pos);
  void addMouse(Position pos);
  void addStone(Position pos);
  void addBushes(Position pos);
  void addBrick(Position pos);

  void takeInput();
  void moveBots();
  void collideBullets();
  void checkBulletBlockCollisions();
  void checkBulletTankCollisions();

 private:
  Player player;
  std::string levelName;
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  bool isRunning = true;

  std::vector<Tank> tanks;
  std::vector<Bullet> bullets;
  std::vector<Block> blocks;
};

#endif  // BATTLECITY_GAMEPROCESS_SOLOGAME_H_
