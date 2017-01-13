#include "Motor.h"

int _state = 0;
int _speed = 0;
String _direction = "";

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
  if(direction == "right"){ // or fwd...
    dir[0] = HIGH;
    dir[1] = LOW;
  }
  else if(direction == "left"){ //or bwd...
    dir[0] = LOW;
    dir[1] = HIGH;
  }
  return dir;
}

void Motor::setSpeed(int speed){
  if(speed > -10 && speed < 10) {
      disable();
  } else {
    if(_state == 0) {
      enable();
    }
    
    _speed = 50 + abs(speed);
    analogWrite(speed > 0 ? _pin1 : _pin2, _speed);
    digitalWrite(speed < 0 ? _pin1 : _pin2, LOW);
  }
}

// Set direction of the motor, using language
void Motor::setDirection(String direction){
  _direction = direction;
  digitalWrite(_pin1, _directions(direction)[0]);
  digitalWrite(_pin2, _directions(direction)[1]);
}

// Start motor
void Motor::enable(){
  _state = 1;
  digitalWrite(_enable, HIGH);
}

// Stop motor
void Motor::disable(){
   _state = 0;
  digitalWrite(_enable, LOW);
}
