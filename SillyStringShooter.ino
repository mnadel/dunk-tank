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

int translateIR() {
  switch (results.value)
  {
    case 0xFFA25D: Serial.println("PWER"); break;
    case 0xFFE21D: Serial.println("FUNC/STP"); break;
    case 0xFF629D: Serial.println("V+"); break;
    case 0xFF22DD: Serial.println("FFR"); break;
    case 0xFF02FD: Serial.println("PLY"); break;
    case 0xFFC23D: Serial.println("FFD"); break;
    case 0xFFE01F: Serial.println("DWN"); break;
    case 0xFFA857: Serial.println("V-"); break;
    case 0xFF906F: Serial.println("UP"); break;
    case 0xFF9867: Serial.println("EQ"); break;
    case 0xFFB04F: Serial.println("ST/RPT"); break;
    case 0xFF6897: Serial.println("0"); return 0;
    case 0xFF30CF: Serial.println("1"); return 1;
    case 0xFF18E7: Serial.println("2"); return 2;
    case 0xFF7A85: Serial.println("3"); return 3;
    case 0xFF10EF: Serial.println("4"); return 4;
    case 0xFF38C7: Serial.println("5"); return 5;
    case 0xFF5AA5: Serial.println("6"); return 6;
    case 0xFF42BD: Serial.println("7"); return 7;
    case 0xFF4AB5: Serial.println("8"); return 8;
    case 0xFF52AD: Serial.println("9"); return 9;
    case 0xFFFFFFFF: Serial.println("REPEAT"); break;
    default:
      Serial.println(results.value, HEX);
  }

  delay(500); // Do not get immediate repeat
  return -1;
}

void setup()
{
  Serial.begin(9600);
  Serial.println("starting");

  servo.attach(SERVO_PIN);
  irrecv.enableIRIn();
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  digitalWrite(LED_BUILTIN, LOW);

  if (irrecv.decode(&results))
  {
    int pressed = translateIR();

    if (pressed == 5) {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println("triggering");

      servo.write(ACTIVATE_ANGLE);
      delay(ACTIVATION_DURATION);
      servo.write(DEACTIVATE_ANGLE);
    }

    irrecv.resume();
  }
}
