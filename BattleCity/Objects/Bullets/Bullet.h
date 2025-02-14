#ifndef BATTLECITY__BULLET_H_
#define BATTLECITY__BULLET_H_

#include "../Object.h"

class Tank; // это просто для метода getOwner, РОМА ДОПИЛИ ЭТУ ХРЕНЬ ПЖЖ

class Bullet : public Object {
 public:
  Bullet(SDL_Renderer* renderer, Position position, Direction direction, Tank* owner);

  void move();
  void update() override;
  bool isOutside();
  Tank* getOwner();
  std::string type() const override { return "Bullet"; }
 protected:
  int speed;
  Tank* owner;
};




#endif //BATTLECITY__BULLET_H_
