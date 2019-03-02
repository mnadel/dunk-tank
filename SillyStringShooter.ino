#include <Servo.h>
#include "NewPing.h"

// hardware control
const int ECHO_PIN = 11;
const int TRIGGER_PIN = 12;
const int SERVO_PIN = 9;

// sonar logic
const int ACQUIRE_DIST = 12;
const int REACQUIRE_DIST = 24;

// servo logic
const int ACTIVATE_ANGLE = 180;
const int ACTIVATION_DURATION = 750;
const int DEACTIVATE_ANGLE = 0;
const int PINGS = 10;

// state
NewPing sonar(TRIGGER_PIN, ECHO_PIN);
Servo servo;

bool acquired = false;
bool searching = true;
long currDist;
long prevDist;

void setup() {
  Serial.begin(9600);
  servo.attach(SERVO_PIN);
}

void loop() {
  currDist = NewPing::convert_in(sonar.ping_median(PINGS));

  acquired = searching && currDist <= ACQUIRE_DIST;
  searching = currDist > REACQUIRE_DIST;

  log();

  if (acquired) {
    servo.write(ACTIVATE_ANGLE);
    delay(ACTIVATION_DURATION);
    servo.write(DEACTIVATE_ANGLE);
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
