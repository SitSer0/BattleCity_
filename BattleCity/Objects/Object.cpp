#include "Object.h"

void Object::updateTexture() {
  if (texture != nullptr) {
    SDL_DestroyTexture(texture);
    texture = nullptr;
  }

  auto it = imagePath.find(direction);
  if (it != imagePath.end()) {
    SDL_Surface* surface = IMG_Load(it->second.c_str());
    if (surface == nullptr) {
      std::cerr << "Не удалось загрузить изображение: " << IMG_GetError() << '\n';
      return;
    }

    texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    if (texture == nullptr) {
      std::cerr << "Не удалось создать текстуру: " << SDL_GetError() << '\n';
    }
  }
}

void Object::Draw() const {
  if (texture == nullptr) {
    std::cerr << "Текстура объекта не загружена\n";
    return;
  }

  SDL_Rect destRect;
  destRect.x = position.x - (size.sizeX / 2);
  destRect.y = position.y - (size.sizeY / 2);
  destRect.w = size.sizeX;
  destRect.h = size.sizeY;

  // Отрисовываем текущую текстуру на рендерере
  SDL_RenderCopy(renderer, texture, NULL, &destRect);
}

bool Object::isTouch(Object* other) {
  return (2 * abs(position.x - other->position.x) < (size.sizeX + other->size.sizeX)) && (2 * abs(position.y - other->position.y) < (size.sizeY + other->size.sizeY));
}

std::string Object::type() const {
  return "Object";
}

