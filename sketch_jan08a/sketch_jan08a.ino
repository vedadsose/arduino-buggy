#include "Motor.h"

Motor steer(9, 7, 8);
Motor drive(4, 5, 6);

void setup() {
  Serial.begin(9600);
//  drive.setDirection("fwd");
//  steer.setDirection("left");
//  delay(1000);
//  steer.disable();
//  drive.disable();
//  delay(1000);
//  steer.enable();
//  drive.enable();
//  drive.setDirection("bwd");
//  steer.setDirection("right");
//  delay(1000);
//  drive.setSpeed(50);
//  delay(5000);
//  drive.disable();
//  steer.disable();
}

void loop() {
  // Listen to serial port
  if (Serial.available() > 0) {
    String incoming = "";
    char character;

    while(Serial.available()) {
      character = Serial.read();
      incoming.concat(character);
    }

    if(incoming == "fwd" || incoming == "bwd"){
      drive.setDirection(incoming);
    }

    else if(incoming == "right" || incoming == "left"){
      steer.setDirection(incoming);
    }

    else if(incoming == "straight"){
      steer.disable();
    }

    else if(incoming == "enable steering"){
      steer.enable();
      steer.setSpeed(100);
    }

    else if(incoming == "enable driving"){
      drive.enable();
    }

    else {
      drive.setSpeed(incoming.toInt());
    }
  }
}

