#include "Game.h"

#include <fstream>
#include <utility>
#include <ctime>

#include "../levels/levels.h"

bool keyStates[SDL_NUM_SCANCODES];  // Массив для состояний всех клавиш

Game::Game(std::string fileName, SDL_Window* wind, SDL_Renderer* rend) : levelName(std::move(fileName)), window(wind), renderer(rend) {};

Game::~Game() {
  // delete renderer;
  // delete window;
}

bool Game::Initialize() {
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    return false;
  }

  // window = SDL_CreateWindow("Battle City", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GAME_WEIGHT, GAME_HEIGHT, 0);

  if (!window) {
    SDL_Log("Failed to create window: %s", SDL_GetError());
    return false;
  }

  // renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer) {
    SDL_Log("Failed to create renderer: %s", SDL_GetError());
    return false;
  }

  AddTanks();
  AddBlocks();
  return true;
}

void Game::RunLoop() {
  while (isRunning) {
    SDL_Delay(10);
    ProcessInput();
    UpdateGame();
    GenerateOutput();
  }
}

void Game::Shutdown() {
  // SDL_DestroyWindow(window);
  // SDL_DestroyRenderer(renderer);
  // SDL_Quit();
  for (auto* tank : tanks) {
    if (tank) {
      delete tank;
      tank = nullptr;
    }
  }
  for (auto* bullet : bullets) delete bullet;
  for (auto* block : blocks) delete block;
}

void Game::addT34(Position pos) {
  tanks.push_back(new T34(renderer, pos, Direction::RIGHT));
}

void Game::addTiger(Position pos) {
  tanks.push_back(new Tiger(renderer, pos, Direction::RIGHT));
}

void Game::addMouse(Position pos) {
  tanks.push_back(new Mouse(renderer, pos, Direction::RIGHT));
}

void Game::addPanther(Position pos) {
  tanks.push_back(new Panther(renderer, pos, Direction::RIGHT));
}

void Game::addBrick(Position pos) {
  blocks.push_back(
      new Brick(renderer, pos, sizeBlock, Direction::UP, imgBrickWall));
}
void Game::addBushes(Position pos) {
  blocks.push_back(
      new Bushes(renderer, pos, sizeBlock, Direction::UP, imgBushes));
}
void Game::addStone(Position pos) {
  blocks.push_back(
      new Stone(renderer, pos, sizeBlock, Direction::UP, imgStone));
}

void Game::AddTanks() {
  //addPanther(Position(400, 400));
  //addPanther(Position(500, 500));
  //addMouse(Position(500, 700));
}

void Game::ProcessInput() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      isRunning = false;
    } else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
      // Обновляем состояние клавиши
      int key = event.key.keysym.scancode;
      bool isPressed = (event.type == SDL_KEYDOWN);
      keyStates[key] = isPressed;
    }
  }
}

void Game::takeInput() {
  if (!playerTank) {
    return;
  }
  if (keyStates[SDL_SCANCODE_LEFT]) {
    bool canMove = true;
    for (auto tank : tanks) {
      if (tank != playerTank) {
        canMove &= playerTank->canMoveLeft(*tank);
      }
    }
    for (auto block : blocks) {
      // std::cout << block->type() << "\n";
      if (block->type() != "Bushes") {
        canMove &= playerTank->canMoveLeft(*block);
      }
    }
    playerTank->setDirection(Direction::LEFT);
    playerTank->updateTexture();
    if (canMove) {
      playerTank->moveLeft();
    }
  }
  if (keyStates[SDL_SCANCODE_RIGHT]) {
    bool canMove = true;
    for (auto tank : tanks) {
      if (tank != playerTank) {
        canMove &= playerTank->canMoveRight(*tank);
      }
    }
    for (auto block : blocks) {
      // std::cout << block->type() << "\n";
      if (block->type() != "Bushes") {
        canMove &= playerTank->canMoveRight(*block);
      }
    }
    playerTank->setDirection(Direction::RIGHT);
    playerTank->updateTexture();

    if (canMove) {
      playerTank->moveRight();
    }
  }
  if (keyStates[SDL_SCANCODE_UP]) {
    bool canMove = true;
    for (auto tank : tanks) {
      if (tank != playerTank) {
        canMove &= playerTank->canMoveUp(*tank);
      }
    }
    for (auto block : blocks) {
      // std::cout << block->type() << "\n";
      if (block->type() != "Bushes") {
        canMove &= playerTank->canMoveUp(*block);
      }
    }
    playerTank->setDirection(Direction::UP);
    playerTank->updateTexture();
    if (canMove) {
      playerTank->moveUp();
    }
  }
  if (keyStates[SDL_SCANCODE_DOWN]) {
    bool canMove = true;
    for (auto tank : tanks) {
      if (tank != playerTank) {
        canMove &= playerTank->canMoveDown(*tank);
      }
    }
    for (auto block : blocks) {
      // std::cout << block->type() << "\n";
      if (block->type() != "Bushes") {
        canMove &= playerTank->canMoveDown(*block);
      }
    }
    playerTank->setDirection(Direction::DOWN);
    playerTank->updateTexture();
    if (canMove) {
      playerTank->moveDown();
    }
  }
  if (keyStates[SDL_SCANCODE_SPACE] && playerTank->canShoot()) {
    Bullet* newBullet = playerTank->shoot();
    bullets.push_back(newBullet);
  }
  if (keyStates[SDL_SCANCODE_ESCAPE]) {
    std::cout << "exit\n";
    isRunning = false;
    return;
  }
}

void Game::UpdateGame() {
  takeInput(); // обработка нажатий
  moveBots();   // механика ботов
  updateBullets();  // проверка составления пуль между собой
  updateOutsideBullets();   // проверка выхода пуль за пределы карты
  updateKillBlocks();   // Проверяем столкновения между пулями и блоками
  updateKillTanks();   // Проверяем столкновения между пулями и танками
}

void Game::GenerateOutput() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black background
  SDL_RenderClear(renderer);

  // Отрисовывайте танки, пули и блоки
  for (const auto& tank : tanks) {
    tank->Draw();
  }
  for (const auto& bullet : bullets) {
    bullet->Draw();
  }
  for (const auto& block : blocks) {
    block->Draw();
  }
  SDL_RenderPresent(renderer);
}

void Game::AddBlocks() {
  std::ifstream file("../levels/" + levelName + ".txt");
  if (!file.is_open()) {
    std::cerr << "Ошибка при открытии файла для чтения." << std::endl;
    return;
  }
  for (int i = 0; i < 26; ++i) {
    std::string line;
    getline(file, line);
    for (int j = 0; j < 27; ++j) {
      if (line[j] == '1') {
        addBrick(Position(300 + j * sizeBlock.sizeX,
                          30 + i * sizeBlock.sizeY));
      }
      if (line[j] == '3') {
        addStone(Position(300 + j * sizeBlock.sizeX,
                          30 + i * sizeBlock.sizeY));
      }
      if (line[j] == '2') {
        addBushes(Position(300 + j * sizeBlock.sizeX,
                           30 + i * sizeBlock.sizeY));
      }
    }
  }
  Position tankPosition = {300 + 3 * sizeBlock.sizeX * 2,
                           40 + 1 * sizeBlock.sizeY};
  Direction tankDirection = Direction::DOWN;
  Tank* tank = new Panther(renderer, tankPosition, tankDirection);
  playerTank = tank;
  tanks.push_back(playerTank);
  file.close();
}


void Game::moveBots() {
  for (size_t i = 0; i < tanks.size(); ++i) {
    if (tanks[i] != playerTank) {
      bool canMoveInCurrentDirection = true;
      for (Object* obstacle : blocks) {
        if (obstacle->type() == "Bushes") {
          continue;
        }
        if (tanks[i]->getDirection() == Direction::DOWN && !tanks[i]->canMoveDown(*obstacle)) {
          canMoveInCurrentDirection = false;
          break;
        }
        if (tanks[i]->getDirection() == Direction::UP && !tanks[i]->canMoveUp(*obstacle)) {
          canMoveInCurrentDirection = false;
          break;
        }
        if (tanks[i]->getDirection() == Direction::LEFT && !tanks[i]->canMoveLeft(*obstacle)) {
          canMoveInCurrentDirection = false;
          break;
        }
        if (tanks[i]->getDirection() == Direction::RIGHT && !tanks[i]->canMoveRight(*obstacle)) {
          canMoveInCurrentDirection = false;
          break;
        }
      }

      // Если врезались в стену или препятствие, выбираем новое направление
      if (!canMoveInCurrentDirection) {
        std::vector<Direction> directions = {Direction::UP, Direction::DOWN, Direction::LEFT, Direction::RIGHT};
        Direction newDirection;
        bool directionFound = false;

        while (!directionFound) {
          newDirection = directions[rand() % directions.size()];
          directionFound = true;
          for (Object* obstacle : blocks) {
            if (newDirection == Direction::DOWN && tanks[i]->getDirection() == Direction::DOWN && !tanks[i]->canMoveDown(*obstacle)) {
              directionFound = false;
              break;
            }
            if (newDirection == Direction::UP && tanks[i]->getDirection() == Direction::UP && !tanks[i]->canMoveUp(*obstacle)) {
              directionFound = false;
              break;
            }
            if (newDirection == Direction::LEFT && tanks[i]->getDirection() == Direction::LEFT && !tanks[i]->canMoveLeft(*obstacle)) {
              directionFound = false;
              break;
            }
            if (newDirection == Direction::RIGHT && tanks[i]->getDirection() == Direction::RIGHT && !tanks[i]->canMoveRight(*obstacle)) {
              directionFound = false;
              break;
            }
          }
        }
        tanks[i]->setDirection(newDirection);
      }

      // Двигаемся в выбранном направлении
      switch (tanks[i]->getDirection()) {
        case Direction::UP:
          tanks[i]->moveUp();
          break;
        case Direction::DOWN:
          tanks[i]->moveDown();
          break;
        case Direction::LEFT:
          tanks[i]->moveLeft();
          break;
        case Direction::RIGHT:
          tanks[i]->moveRight();
          break;
      }
    }

    auto now = std::chrono::steady_clock::now();
    if (std::chrono::duration_cast<std::chrono::seconds>(now - tanks[i]->getLastShootTime()).count() > 1) { // Например, каждые 2 секунды
      if (tanks[i]->canShoot() && tanks[i] != playerTank) {
        Bullet* bullet = tanks[i]->shoot();
        bullets.push_back(bullet);
        tanks[i]->setLastShootTime(now);
      }
    }

  }
}


void Game::updateBullets() {
  for (size_t i = 0; i < bullets.size(); ++i) {
    bullets[i]->update();
  }
  for (auto it1 = bullets.begin(); it1 != bullets.end();) {
    bool bulletRemoved1 = false;
    for (auto it2 = it1 + 1; it2 != bullets.end();) {
      if ((*it1)->isTouch(*it2)) {
        ((*it1)->getOwner())->setExistingBullet(nullptr);
        ((*it2)->getOwner())->setExistingBullet(nullptr);
        it2 = bullets.erase(it2);
        it1 = bullets.erase(it1);
        bulletRemoved1 = true;
        break;
      } else {
        ++it2;
      }
    }
    if (!bulletRemoved1) {
      ++it1;
    }
  }
}


void Game::updateOutsideBullets() {
  for (auto it = bullets.begin(); it != bullets.end();) {
    if ((*it)->isOutside()) {
      (*it)->getOwner()->setExistingBullet(nullptr);
      delete *it;  // Удаляем объект пули
      it = bullets.erase(it);  // Удаляем указатель из вектора и получаем
                               // итератор на следующий элемент
    } else {
      ++it;  // Переходим к следующему элементу, если пуля не была удалена
    }
  }
}


void Game::updateKillTanks() {
  for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
    bool bulletRemoved = false;
    for (auto tankIt = tanks.begin(); tankIt != tanks.end() && !bulletRemoved;) {
      if ((*bulletIt)->isTouch(*tankIt)) {
        (*tankIt)->hit();
        if ((*tankIt)->getHealth() <= 0) {
          // Удаляем танк при столкновении
          delete *tankIt;
          tankIt = tanks.erase(tankIt);
        }
        Tank* ownerTank = (*bulletIt)->getOwner();
        ownerTank->setExistingBullet(nullptr);
        // Удаляем пулю и выходим из внутреннего цикла
        // bulletIt->owner
        delete *bulletIt;
        bulletIt = bullets.erase(bulletIt);
        bulletRemoved = true;

      } else {
        ++tankIt; //только если элемент не был удален
      }
    }
    if (!bulletRemoved) {
      ++bulletIt;  //только если пуля не была удалена
    } else {
      break;
    }
  }
}


void Game::updateKillBlocks() {
  for (auto bulletIt = bullets.begin(); bulletIt != bullets.end();) {
    bool bulletRemoved = false;
    for (auto blockIt = blocks.begin(); blockIt != blocks.end();) {
      if ((*blockIt)->type() != "Bushes" && (*bulletIt)->isTouch(*blockIt)) {
        // Удаляем блок
        if ((*blockIt)->type() == "Brick") {
          blockIt = blocks.erase(blockIt);
        } else {
          ++blockIt;
        }

        // Удаляем пулю и выходим из внутреннего цикла
        bulletRemoved = true;
      } else {
        ++blockIt;  // только если элемент не был удален
      }
    }
    if (!bulletRemoved) {
      ++bulletIt;  // только если пуля не была удалена
    } else {
      Tank* ownerTank = (*bulletIt)->getOwner();
      ownerTank->setExistingBullet(nullptr);
      bulletIt = bullets.erase(bulletIt);
      break;
    }
  }
}

