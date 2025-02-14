#ifndef GAME_H
#define GAME_H

#include <SDL.h>

#include <memory>
#include <vector>

#include "../Objects/Blocks/Block.h"
#include "../Objects/Bullets/Bullet.h"
#include "../Objects/Object.h"
#include "../Objects/Tanks/Mouse/Mouse.h"
#include "../Objects/Tanks/Panther/Panther.h"
#include "../Objects/Tanks/T34/T34.h"
#include "../Objects/Tanks/Tank.h"
#include "../Objects/Tanks/Tiger/Tiger.h"
#include "../Objects/Blocks/Bushes/Bushes.h"
#include "../Objects/Blocks/BrickWall/Brick.h"
#include "../Objects/Blocks/Stone/Stone.h"

class Game {
 public:
  Game(std::string fileName, SDL_Window* wind, SDL_Renderer* rend);
  ~Game();
  bool Initialize();
  void RunLoop();
  void Shutdown();

 private:
  void ProcessInput();
  void takeInput();
  void UpdateGame();
  void GenerateOutput();
  void AddTanks();
  void AddBlocks();

  void moveBots();
  void updateBullets();
  void updateOutsideBullets();
  void updateKillTanks();
  void updateKillBlocks();

  void addT34(Position pos);
  void addTiger(Position pos);
  void addPanther(Position pos);
  void addMouse(Position pos);
  void addStone(Position pos);
  void addBushes(Position pos);
  void addBrick(Position pos);

  std::string levelName;

  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  bool isRunning = true;

  Tank* playerTank = nullptr;
  std::vector<Tank*> tanks;
  std::vector<Bullet*> bullets;
  std::vector<Block*> blocks;
};

#endif  // GAME_H
