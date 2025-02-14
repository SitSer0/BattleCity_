#include "CreatingLevel.h"


CreatingLevels::CreatingLevels(SDL_Window* wind, SDL_Renderer* rend) : window(wind), renderer(rend) {
  initSDL();
  textures[0] =
      loadTexture("../Objects/Blocks/BrickWall/brick_wall.png", renderer);
  textures[1] = loadTexture("../Objects/Blocks/Bushes/bushes.png", renderer);
  textures[2] = loadTexture("../Objects/Blocks/Stone/stone.png", renderer);
  mainLoop();
}

CreatingLevels::~CreatingLevels() {
  // SDL_DestroyRenderer(renderer);
  // SDL_DestroyWindow(window);
  // SDL_Quit();
}

void CreatingLevels::initSDL() {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError()
              << std::endl;
    exit(1);
  }

  // window = SDL_CreateWindow("Creating Levels", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight,SDL_WINDOW_SHOWN);
  if (!window) {
    std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError()
              << std::endl;
    exit(1);
  }

  // renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    std::cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError()
              << std::endl;
    exit(1);
  }
}

SDL_Texture *CreatingLevels::loadTexture(const std::string &path,
                                         SDL_Renderer *renderer) {
  SDL_Surface *surface = IMG_Load(path.c_str());
  if (!surface) {
    std::cerr << "Ошибка при загрузке изображения: " << IMG_GetError()
              << std::endl;
    return nullptr;
  }
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);
  if (!texture) {
    std::cerr << "Ошибка при создании текстуры: " << SDL_GetError()
              << std::endl;
  }
  return texture;
}

void CreatingLevels::drawGrid() {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

  for (int y = 0; y < gridSize; ++y) {
    for (int x = 0; x < gridSize; ++x) {
      SDL_Rect destRect = {x * cellSize, y * cellSize, cellSize, cellSize};

      bool flag = false;

      for (size_t i = 0; i < BadCells.size(); ++i) {
        if (BadCells[i] == Position(x, y)) {
          flag = true;
          break;
        }
      }

      if (flag) {
        SDL_RenderCopy(renderer, textures[0], nullptr, &destRect);
      }

      if (x == 0 || x == 25 || y == 0 || y == 25) {
        SDL_RenderCopy(renderer, textures[2], nullptr, &destRect);
      }

//      if (std::find(BadCells.begin(), BadCells.end(), Position(x, y)) != BadCells.end()) {
//        SDL_RenderCopy(renderer, textures[2], nullptr, &destRect);
//      }

      if (grid[y][x] == "1") {
        SDL_RenderCopy(renderer, textures[0], nullptr, &destRect);
      } else if (grid[y][x] == "2") {
        SDL_RenderCopy(renderer, textures[1], nullptr, &destRect);
      } else if (grid[y][x] == "3") {
        SDL_RenderCopy(renderer, textures[2], nullptr, &destRect);
      }
    }
  }
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);  // Цвет сетки
  for (int i = 0; i <= gridSize; ++i) {
    SDL_RenderDrawLine(renderer, i * cellSize, 0, i * cellSize, windowHeight);
    SDL_RenderDrawLine(renderer, 0, i * cellSize, windowWidth, i * cellSize);
  }
}

void CreatingLevels::mainLoop() {
  bool running = true;
  SDL_Event e;
  char inputText[256] = "";
  SDL_StartTextInput();
  while (running) {
    while (SDL_PollEvent(&e) != 0) {
      if (e.type == SDL_QUIT) {
        running = false;
      }
      if (e.type == SDL_TEXTINPUT) {
        strcat(inputText, e.text.text);
      }
      int x, y;
      Uint32 buttons = SDL_GetMouseState(&x, &y);
      if (buttons & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        handleMouseClick(std::min(std::max(x, 0), windowWidth),
                         std::min(std::max(y, 0), windowHeight));
      }
      if (e.type == SDL_KEYDOWN) {
        switch (e.key.keysym.sym) {
          case SDLK_1:
            typeBlock = "1";
            break;
          case SDLK_2:
            typeBlock = "2";
            break;
          case SDLK_3:
            typeBlock = "3";
            break;
          case SDLK_BACKSPACE:
            typeBlock = " ";
            break;
          case SDLK_0:
            SaveLevel();
            break;
          case SDLK_ESCAPE:
            running = false;
            break;
        }
      }
    }
    drawGrid();
    SDL_RenderPresent(renderer);
  }
  // SDL_DestroyRenderer(renderer);
  // SDL_DestroyWindow(window);
  // SDL_Quit();
}

void CreatingLevels::handleMouseClick(int x, int y) {
  if (x >= windowWidth || x <= 0 || y >= windowHeight || y <= 0) {
    return;
  }

  int gridX = x / cellSize;
  int gridY = y / cellSize;

  bool flag = false;

  for (size_t i = 0; i < BadCells.size(); ++i) {
    if (BadCells[i] == Position(gridX, gridY)) {
      flag = true;
      break;
    }
  }

  if (flag || gridX == 0 || gridX == 25 || gridY == 0 || gridY == 25) {
    return;
  }



  grid[gridY][gridX] = typeBlock;
}

void CreatingLevels::SaveLevel() {
  std::string file_name;
  std::cout << "Введите имя нового уровня: ";
  std::cin >> file_name;
  std::ofstream file("../levels/" + file_name + ".txt");
  if (!file.is_open()) {
    std::cerr << "Ошибка при открытии файла для записи." << std::endl;
    return;
  }
  for (int i = 0; i < 26; ++i) {
    grid[0][i] = "3";
    grid[i][0] = "3";
    grid[25 - i][25] = "3";
    grid[25][25 - i] = "3";
  }
  for (auto pos: BadCells) {
    grid[pos.y][pos.x] = "1";
  }
  for (int y = 0; y < gridSize; ++y) {
    for (int x = 0; x < gridSize; ++x) {
      file << grid[y][x];
    }
    file << "\n";
  }
  file.close();
  std::cout << "good\n";
}