#include <limits.h>
#include <Servo.h>
#include "NewPing.h"

// hardware control
const int echoPin = 11;
const int triggerPin = 12;
const int servoPin = 9;

NewPing sonar(triggerPin, echoPin);
Servo servo;

// sonar logic
const int acquireDist = 12;
const int reacquireDist = 24;

bool acquired = false;
bool searching = true;
long currDist;
long prevDist;

// servo logic
const int activateAngle = 180;
const int activationDuration = 750;
const int deactivateAngle = 0;
const int pings = 5;

void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);
}

void loop() {
  currDist = NewPing::convert_in(sonar.ping_median(pings));
 
  acquired = searching && currDist <= acquireDist;
  searching = currDist > reacquireDist;

  log();

  if (acquired) {
    servo.write(activateAngle);
    delay(activationDuration);
    servo.write(deactivateAngle);
  }

  prevDist = currDist;
}

void log() {
  Serial.print("dist=");
  Serial.print(currDist);
  Serial.print(", acq=");
  Serial.print(acquired ? "1" : "0");
  Serial.print(", srch=");
  Serial.println(searching ? "1" : "0");
}
