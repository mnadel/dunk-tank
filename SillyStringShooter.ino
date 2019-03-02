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
const int PINGS = 7;

// state
NewPing sonar(TRIGGER_PIN, ECHO_PIN);
Servo servo;

bool acquired = false;
bool searching = true;
long currDist;
long prevDist;

void setup() {
  Serial.begin(9600);
  Serial.println("starting");
  
  servo.attach(SERVO_PIN);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  currDist = NewPing::convert_in(sonar.ping_median(PINGS));

  acquired = searching && currDist <= ACQUIRE_DIST;
  searching = currDist >= REACQUIRE_DIST;

  log(currDist, searching);

  if (searching) {
    digitalWrite(LED_BUILTIN, HIGH);
  }

  if (acquired) {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("triggering");
    servo.write(ACTIVATE_ANGLE);
    delay(ACTIVATION_DURATION);
    servo.write(DEACTIVATE_ANGLE);
  }

  prevDist = currDist;
}

void log(long dist, bool searching) {
  Serial.print("dist=");
  Serial.print(dist);
  Serial.print(", srch=");
  Serial.println(searching ? "1" : "0");
}
