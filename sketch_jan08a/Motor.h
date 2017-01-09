#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor {
  private:
    int _enable;
    int _pin1;
    int _pin2;
    String _direction;
    int _speed;
  public:
    Motor(int enablePin, int pin1, int pin2);
    ~Motor();
    void setDirection(String direction);
    void inverseDirection();
    void setSpeed(int speed);
    void enable();
    void disable();
};

#endif

