

#include "Tank.h"
#include <random>

Tank::Tank(SDL_Renderer *renderer, Position position, Size size,
           Direction direction, int health, int speed,
           const std::map<Direction, std::string> &imagePath)
    : Object(renderer, position, size, direction, imagePath),
      health(health),
      speed(speed),
      existingBullet(nullptr),
      lastShootTime(std::chrono::steady_clock::now()){};

void Tank::moveLeft() {
  direction = Direction::LEFT;
  if (position.x >= size.sizeX / 2) {
    position.x -= speed;
  }
  updateTexture();
}

void Tank::moveDown() {
  direction = Direction::DOWN;
  if (position.y <= GAME_HEIGHT - size.sizeY / 2) {
    position.y += speed;
  }
  updateTexture();
}

void Tank::moveRight() {
  direction = Direction::RIGHT;
  if (position.x <= GAME_WEIGHT - size.sizeX / 2) {
    position.x += speed;
  }
  updateTexture();
}

void Tank::moveUp() {
  direction = Direction::UP;
  if (position.y >= size.sizeY / 2) {
    position.y -= speed;
  }
  updateTexture();
}

void Tank::death(){};

void Tank::hit() {
  health -= bulletDamage;
  if (health <= 0) {
    death();
  }
}

Bullet *Tank::getExistingBullet() { return existingBullet; }

bool Tank::canShoot() {
  return !getExistingBullet() &&
         (std::chrono::duration_cast<std::chrono::milliseconds>(
              std::chrono::steady_clock::now() - lastShootTime)
              .count() > 500);
}

Bullet *Tank::shoot() {
  if (!canShoot()) {
    return nullptr;  // Если нельзя стрелять, возвращаем nullptr
  }
  lastShootTime = std::chrono::steady_clock::now();

  Position newBulletPosition =
      position;  // Используем текущую позицию танка как начальную для пули
  // Рассчитываем новую позицию пули на основе направления танка
  switch (direction) {
    case Direction::DOWN:
      newBulletPosition.y += (sizeBullet.sizeY + sizeTank.sizeY) / 2;
      break;  // Не забываем добавить break
    case Direction::UP:
      newBulletPosition.y -= (sizeBullet.sizeY + sizeTank.sizeY) / 2;
      break;
    case Direction::LEFT:
      newBulletPosition.x -= (sizeBullet.sizeX + sizeTank.sizeX) / 2;
      break;
    case Direction::RIGHT:
      newBulletPosition.x += (sizeBullet.sizeX + sizeTank.sizeX) / 2;
      break;
  }


  existingBullet = new Bullet(renderer, newBulletPosition, direction, this);
  return existingBullet;  // Возвращаем созданную пулю
}

void Tank::setExistingBullet(Bullet *newBullet) { existingBullet = newBullet; }

bool Tank::canMoveDown(Object &other) {
  if ((position.x <
       other.getPosition().x + (size.sizeX + other.getSize().sizeX) / 2) &&
      (position.x >
       other.getPosition().x - (size.sizeX + other.getSize().sizeX) / 2) &&
      (position.y + speed < other.getPosition().y &&
       (position.y + speed >
        other.getPosition().y - (size.sizeY + other.getSize().sizeY) / 2))) {
    return false;
  }
  return true;
}

bool Tank::canMoveUp(Object &other) {
  if ((position.x <
       other.getPosition().x + (size.sizeX + other.getSize().sizeX) / 2) &&
      (position.x >
       other.getPosition().x - (size.sizeX + other.getSize().sizeX) / 2) &&
      (position.y - speed <
       other.getPosition().y + (size.sizeY + other.getSize().sizeY) / 2) &&
      (position.y - speed > other.getPosition().y)) {
    return false;
  }
  return true;
}

bool Tank::canMoveLeft(Object &other) {
  if ((position.x - speed <
       other.getPosition().x + (size.sizeX + other.getSize().sizeX) / 2) &&
      (position.x - speed >
       other.getPosition().x - (size.sizeX + other.getSize().sizeX) / 2) &&
      (position.y >
       other.getPosition().y - (size.sizeY + other.getSize().sizeY) / 2) &&
      (position.y <
       other.getPosition().y + (size.sizeY + other.getSize().sizeY) / 2)) {
    return false;
  }
  return true;
}

bool Tank::canMoveRight(Object &other) {
  if ((position.y <
       other.getPosition().y + (size.sizeY + other.getSize().sizeY) / 2) &&
      (position.y >
       other.getPosition().y - (size.sizeY + other.getSize().sizeY) / 2) &&
      (position.x + speed < other.getPosition().x &&
       (position.x + speed >
        other.getPosition().x - (size.sizeX + other.getSize().sizeX) / 2))) {
    return false;
  }
  return true;
}

bool Tank::canMove(Direction direct, Object &other) {  // допилить если надо
  if (position.x < 1000 && position.x > -100 && position.y < 100 &&
      position.y > -100) {
    return false;
  }
  return true;
}

Direction Tank::getDirection() { return direction; }

void Tank::setDirection(Direction direction1) { direction = direction1; }

int Tank::getHealth() {
  return health;
}

void Tank::EnemyMove(std::vector<Object*>& obstacles) {
  // Проверяем, можем ли мы двигаться в текущем направлении
  bool canMoveInCurrentDirection = true;
  for (auto* obstacle : obstacles) {
    if (!canMove(direction, *obstacle)) {
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
      for (auto* obstacle : obstacles) {
        if (!canMove(newDirection, *obstacle)) {
          directionFound = false;
          break;
        }
      }
    }

    setDirection(newDirection);
  }

  // Двигаемся в выбранном направлении
  switch (getDirection()) {
    case Direction::UP:
      moveUp();
      break;
    case Direction::DOWN:
      moveDown();
      break;
    case Direction::LEFT:
      moveLeft();
      break;
    case Direction::RIGHT:
      moveRight();
      break;
  }
}



void Tank::update(std::vector<Object*>& obstacles) {
  EnemyMove(obstacles);


  auto now = std::chrono::steady_clock::now();
  if (std::chrono::duration_cast<std::chrono::seconds>(now - lastShootTime).count() > 2) { // Например, каждые 2 секунды
    if (canShoot()) {
      Bullet* bullet = shoot();
    }
    lastShootTime = now;
  }
}

void Tank::setLastShootTime(const std::chrono::steady_clock::time_point& newLastShootTime) {
  lastShootTime = newLastShootTime;
}

// Возвращает время последнего выстрела
std::chrono::steady_clock::time_point Tank::getLastShootTime() const {
  return lastShootTime;
}
