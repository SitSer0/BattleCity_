#ifndef BATTLECITY__TANK_H_
#define BATTLECITY__TANK_H_

#include <chrono>
#include <vector>

#include "../Bullets/Bullet.h"  // фф
#include "../Object.h"

class Tank : public Object {
 public:
  Tank(SDL_Renderer* renderer, Position position, Size size,
       Direction direction, int health, int speed,
       const std::map<Direction, std::string>& imagePath);

  void moveLeft();
  void moveRight();
  void moveDown();
  void moveUp();

  void hit();
  void death();

  void EnemyMove(std::vector<Object*>& obstacles);

  bool canMove(Direction direct, Object& other);

  bool canMoveLeft(Object& other);
  bool canMoveRight(Object& other);
  bool canMoveDown(Object& other);
  bool canMoveUp(Object& other);

  std::chrono::steady_clock::time_point getLastShootTime() const;
  void setLastShootTime(const std::chrono::steady_clock::time_point& newLastShootTime);

  Direction getDirection();
  void setDirection(Direction direction1);

  int getHealth();

  Bullet* getExistingBullet();
  void setExistingBullet(Bullet* newBullet);
  bool canShoot();
  Bullet* shoot();


  void update() override {

  }

  void update(std::vector<Object*>& obstacles);

 protected:
  int health;
  int speed;
  Bullet* existingBullet;
  std::chrono::steady_clock::time_point lastShootTime;
};

#endif  // BATTLECITY__TANK_H_