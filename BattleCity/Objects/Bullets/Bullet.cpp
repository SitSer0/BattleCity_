#include "Bullet.h"

Bullet::Bullet(SDL_Renderer* renderer, Position position, Direction direction,
               Tank* owner)
    : Object(renderer, position, sizeBullet, direction, imgBullet),
      speed(bulletSpeed),
      owner(owner) {
  if (direction == Direction::LEFT || direction == Direction::RIGHT) {
    std::swap(size.sizeY, size.sizeX);
  }
};

void Bullet::move() {
  switch (direction) {
    case Direction::DOWN:
      position.y += speed;
      break;
    case Direction::UP:
      position.y -= speed;
      break;
    case Direction::LEFT:
      position.x -= speed;
      break;
    case Direction::RIGHT:
      position.x += speed;
      break;
  }
  updateTexture();
}

void Bullet::update() {
  move();
  //std::cout << "Bullet position: " << position.x << ", " << position.y
  //          << " | Direction: " << static_cast<int>(direction) << std::endl;
}

Tank* Bullet::getOwner() { return owner; }

bool Bullet::isOutside() {
  return !((position.x < 1024) && (position.x > 0) && (position.y < 768) && (position.y > 0));
}