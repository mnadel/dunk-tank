#include <IRremote.h>
#include <IRremoteInt.h>
#include <Servo.h>

// arduino
const int SERVO_PIN = 9;
const int IRRECV_PIN = 11;

// servo
Servo servo;
const int ACTIVATE_ANGLE = 180;
const int ACTIVATION_DURATION = 750;
const int DEACTIVATE_ANGLE = 0;

// infrared receiver
IRrecv irrecv(IRRECV_PIN);
decode_results results;

// state management
const int KEYPRESS_THRESHOLD_MS = 750;
long lastReceiveTime;
int lastValueReceived = -1;

// math challenge
const int ANSWER = 14;

void setup()
{
  Serial.begin(9600);
  Serial.println("starting");

  servo.attach(SERVO_PIN);
  irrecv.enableIRIn();
  pinMode(LED_BUILTIN, OUTPUT);

  servo.write(DEACTIVATE_ANGLE);
}

unsigned int translateIR() {
  switch (results.value)
  {
    case 0xFF6897: return 0;
    case 0xFF30CF: return 1;
    case 0xFF18E7: return 2;
    case 0xFF7A85: return 3;
    case 0xFF10EF: return 4;
    case 0xFF38C7: return 5;
    case 0xFF5AA5: return 6;
    case 0xFF42BD: return 7;
    case 0xFF4AB5: return 8;
    case 0xFF52AD: return 9;
  }

  return -1;
}

void loop()
{
  digitalWrite(LED_BUILTIN, LOW);

  if (irrecv.decode(&results))
  {
    long receiveTime = millis();
    long timeSinceLastPress = receiveTime - lastReceiveTime;
    int currValue = translateIR();
    
    if (currValue >= 0) {
      Serial.print("pressed=");
      Serial.println(currValue);
      
      if (timeSinceLastPress <= KEYPRESS_THRESHOLD_MS) {
        Serial.print("adding prev=");
        Serial.println(lastValueReceived);
        
        currValue = lastValueReceived*10 + currValue;
      }

      Serial.print("current=");
      Serial.println(currValue);

      if (currValue == ANSWER) {
        digitalWrite(LED_BUILTIN, HIGH);
        Serial.println("triggering");
  
        servo.write(ACTIVATE_ANGLE);
        delay(ACTIVATION_DURATION);
        servo.write(DEACTIVATE_ANGLE);
      }

      lastValueReceived = currValue;
      lastReceiveTime = receiveTime;
    }

    irrecv.resume();
  }
}
