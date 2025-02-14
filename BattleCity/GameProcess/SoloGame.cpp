//
// Created by Serafim on 23.04.2024.
//

#include "SoloGame.h"

SoloGame::SoloGame(std::string fileName, SDL_Window* wind, SDL_Renderer* rend)
    : levelName(std::move(fileName)), window(wind), renderer(rend){};

bool SoloGame::Initialize() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    return false;
  }
  if (!window) {
    SDL_Log("Failed to create window: %s", SDL_GetError());
    return false;
  }
  if (!renderer) {
    SDL_Log("Failed to create renderer: %s", SDL_GetError());
    return false;
  }
  addStarterTanks();
  addStarterBlocks();
  return true;
}

void SoloGame::RunLoop() {
  while (isRunning) {
    SDL_Delay(13);
    playerInput();
    updateGame();
    generateOutput();
  }
}

void SoloGame::ShutDown() { std::cerr << "Game over!" << std::endl; }

void SoloGame::generateOutput() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black background
  SDL_RenderClear(renderer);

  // Отрисовывайте танки, пули и блоки
  for (const auto& tank : tanks) {
    tank.Draw();
  }
  for (const auto& bullet : bullets) {
    bullet.Draw();
  }
  for (const auto& block : blocks) {
    block.Draw();
  }
  SDL_RenderPresent(renderer);
}

void SoloGame::updateGame() {
  takeInput();
  moveBots();
  checkBulletBlockCollisions();
  checkBulletTankCollisions();
  collideBullets();
}

void SoloGame::addT34(Position pos) {
  tanks.push_back(T34(renderer, pos, Direction::UP));
}
void SoloGame::addTiger(Position pos) {
  tanks.push_back(Tiger(renderer, pos, Direction::UP));
}
void SoloGame::addPanther(Position pos) {
  tanks.push_back(Panther(renderer, pos, Direction::UP));
}
void SoloGame::addMouse(Position pos) {
  tanks.push_back(Mouse(renderer, pos, Direction::UP));
}
void SoloGame::addStone(Position pos) {
  blocks.push_back(Stone(renderer, pos));
}
void SoloGame::addBushes(Position pos) {
  blocks.push_back(Bushes(renderer, pos));
}
void SoloGame::addBrick(Position pos) {
  blocks.push_back(Brick(renderer, pos));
}

void SoloGame::playerInput() {}
void SoloGame::addNewTanks() {}
void SoloGame::addStarterBlocks() {}
void SoloGame::addStarterTanks() {}
void SoloGame::takeInput() {}
void SoloGame::moveBots() {}
void SoloGame::collideBullets() {}
void SoloGame::checkBulletBlockCollisions() {}
void SoloGame::checkBulletTankCollisions() {}