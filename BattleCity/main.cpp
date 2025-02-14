#include <chrono>
#include <iostream>
#include <string>
#include <ctime>

#include "CreatingLevels/CreatingLevel.h"
#include "GameProcess/Game.h"

void playSinglePlayer(SDL_Window* wind, SDL_Renderer* rend) {
  std::cout << "Starting single player game...\n";
  Game game("test", wind, rend);
  bool success = game.Initialize();
  if (success) {
    game.RunLoop();
  }
  game.Shutdown();
  std::cout << "all_correct\n";
}

void playMultiPlayer() {
  std::cout << "Starting multi-player game...\n";
  // Здесь логика для многопользовательской игры
}

void createLevel(SDL_Window* window, SDL_Renderer* renderer) {
  std::cout << "Creating a new level...\n";
  CreatingLevels levelCreator(window, renderer);
}

int main() {
  int choice = 0;
  SDL_Init(SDL_INIT_VIDEO);
  IMG_Init(IMG_INIT_PNG); // Инициализация SDL_image для PNG

  SDL_Window* window = SDL_CreateWindow("BattleCity Menu", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, GAME_WEIGHT, GAME_HEIGHT, 0);
  if (!window) {
    printf("Ошибка создания окна: %s\n", SDL_GetError());
    SDL_Quit();
    return 1;
  }

  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    printf("Ошибка создания рендерера: %s\n", SDL_GetError());
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  // Загрузка текстуры
  SDL_Texture* menuTexture = IMG_LoadTexture(renderer, "../Menu.png");
  if (!menuTexture) {
    printf("Ошибка загрузки текстуры: %s\n", IMG_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  SDL_Texture* choiceTexture = IMG_LoadTexture(renderer, "../Objects/Tanks/T34/t34_up.png");
  if (!choiceTexture) {
    printf("Ошибка загрузки текстуры: %s\n", IMG_GetError());
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  int running = 1;
  SDL_Event event;
  int menuOption = 0; // 0 для 1 игрока, 1 для 2 игроков, 2 для создания уровней, 3 для выхода


  SDL_Rect destRect;
  destRect.x = (GAME_WEIGHT - 420) / 2; // Центрирование по горизонтали
  destRect.y = (GAME_HEIGHT - 240) / 2; // Центрирование по вертикали
  destRect.w = 420; // Новая ширина
  destRect.h = 240; // Новая высота

  SDL_Rect choiceRect;
  choiceRect.x = (GAME_WEIGHT - 420) / 2 - 55;
  choiceRect.y = (GAME_HEIGHT - 240) / 2 + 15;
  choiceRect.w = 45;
  choiceRect.h = 45;

  while (running) {
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_QUIT) {
        running = 0;
      } else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
          case SDLK_UP:
            menuOption = (menuOption + 3) % 4; // Переход вверх
            choiceRect.y = (800 - 240) / 2 + 30 + menuOption * 60;
            break;
          case SDLK_DOWN:
            menuOption = (menuOption + 1) % 4; // Переход вниз
            choiceRect.y = (800 - 240) / 2 + 30 + menuOption * 60;
            break;
          case SDLK_RETURN:
            switch (menuOption) {
              case 0:
                playSinglePlayer(window, renderer);
                break;
              case 1:
                playMultiPlayer();
                break;
              case 2:
                createLevel(window, renderer);
                break;
              case 3:
                std::cout << "Exiting game...\n";
                running = false;
                // return 0;
              default:
                std::cout << "Invalid choice, please try again.\n";
                break;
            }
            break;
        }
      }
    }
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, menuTexture, NULL, &destRect); // Отрисовка текстуры
    SDL_RenderCopy(renderer, choiceTexture, NULL, &choiceRect);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}

