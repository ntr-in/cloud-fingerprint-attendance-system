#include <Adafruit_Fingerprint.h>

const int push_button = 25;                       // for changing mode on a button press
                                                  // 0. attendance -> 1. enroll -> 2. delete
                                                  
int mode = 0;
int old_push_val = LOW;

SoftwareSerial mySerial(10, 11);                  // For Fingerprint Sensor
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

void setup() {
  // put your setup code here, to run once:
  pinMode(push_button, INPUT);
  Serial.begin(9600);                             // for debugging

  finger.begin(57600);
  if (finger.verifyPassword()) {
    Serial.println("Found fingerprint sensor!");
  } else {
    Serial.println("Did not find fingerprint sensor :(");
    while (1) { delay(1); }
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  int push_val = digitalRead(push_button);

  if (old_push_val == HIGH && push_val == LOW) {
    mode++;
    mode%=3;
  }

  old_push_val = push_val;
  Serial.println("Mode " + String(mode));

  if (mode == 0) {
    
  }

  delay(500);

}
