#ifndef BATTLECITY__CREATINGLEVEL_H_
#define BATTLECITY__CREATINGLEVEL_H_

#include <SDL_image.h>

#include <fstream>
#include <iostream>
#include <vector>

#include "../constatnti_itd.h"
#include "SDL.h"

class CreatingLevels {
 public:
  CreatingLevels(SDL_Window* wind, SDL_Renderer* rend);
  ~CreatingLevels();

 private:
  std::vector<std::vector<std::string>> grid =
      std::vector<std::vector<std::string>>(26,
                                            std::vector<std::string>(26, " "));
  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  const int windowWidth = 780;
  const int windowHeight = 780;
  const int gridSize = 26;
  const int cellSize = 30;
  std::string typeBlock = " ";
  SDL_Texture* textures[3];

  void initSDL();
  static SDL_Texture* loadTexture(const std::string& path, SDL_Renderer* renderer);
  void drawGrid();
  void mainLoop();
  void handleMouseClick(int x, int y);
  void SaveLevel();
};

#endif  // BATTLECITY__CREATINGLEVEL_H_
