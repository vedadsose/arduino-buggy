#include "Motor.h"

Motor::Motor(int enablePin, int pin1, int pin2){
  _enable = enablePin;
  _pin1 = pin1;
  _pin2 = pin2;

  pinMode (_enable, OUTPUT);
  pinMode (_pin1, OUTPUT);
  pinMode (_pin2, OUTPUT);

  digitalWrite(_enable, HIGH);
}

Motor::~Motor(){
  digitalWrite(_enable, LOW);
}

// Convert language input of direction to usable output (TODO: move somewhere)
int * _directions(String direction){
  static int dir[2];
  if(direction == "fwd" || direction == "right"){
    dir[0] = HIGH;
    dir[1] = LOW;
  }
  else if(direction == "bwd" || direction == "left"){
    dir[0] = LOW;
    dir[1] = HIGH;
  }
  return dir;
}

void Motor::setSpeed(int speed){
  _speed = speed;

  analogWrite((_direction == "fwd" || "right") ? _pin1 : _pin2, speed);
}

// Set direction of the motor, using language
void Motor::setDirection(String direction){
  _direction = direction;

  digitalWrite(_pin1, _directions(direction)[0]);
  digitalWrite(_pin2, _directions(direction)[1]);
}

// Inverse current direction
void Motor::inverseDirection(){
  if(_direction == "fwd") setDirection("bwd");
  if(_direction == "bwd") setDirection("fwd");
  if(_direction == "left") setDirection("right");
  if(_direction == "right") setDirection("left");
}

// Start motor
void Motor::enable(){
  digitalWrite(_enable, HIGH);
}

// Stop motor
void Motor::disable(){
  digitalWrite(_enable, LOW);
}
