#include "Motor.h"

Motor steer(9, 7, 8);
Motor drive(4, 5, 6);

void setup() {
  Serial.begin(9600);
  drive.setDirection("bwd");
  delay(1000);
  drive.disable();
  delay(1000);
  drive.enable();
  drive.inverseDirection();
  delay(1000);
  drive.disable();
}

void loop() {
  // put your main code here, to run repeatedly:
  
}

