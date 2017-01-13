#include "Motor.h"

Motor steer(9, 7, 8);
Motor drive(4, 5, 6);

// Serial communication
String incoming = "";
boolean stringComplete = false;

void setup() {
  Serial.begin(9600);
  incoming.reserve(30);
}

void loop() {
  if (stringComplete) {
    Serial.println(incoming);
    if(incoming == "right" || incoming == "left"){
      Serial.println("Steer!");
      steer.setDirection(incoming);
    }
  
    else if(incoming == "straight"){
      steer.disable();
    }
  
    else {
      drive.setSpeed(incoming.toInt());
    }

    // clear the incoming string:
    incoming = "";
    stringComplete = false;
  }
}

void serialEvent() {
  while (Serial.available()) {
    Serial.println("incoming...");
    // get the new byte:
    char inChar = (char)Serial.read(); 
    //Serial.write(inChar);
    // if the incoming character is a newline or a carriage return, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n' || inChar == '\r') {
      stringComplete = true;
    } 
    else {
      // add it to the incoming:
      incoming += inChar;
    }
  }
}
