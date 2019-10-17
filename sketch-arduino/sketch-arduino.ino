const int push_button = 25;                       // for changing mode on a button press
                                                  // attendance -> enroll -> delete
int mode = 1;
int old_push_val = HIGH;

void setup() {
  // put your setup code here, to run once:
  pinMode(push_button, INPUT);
  Serial.begin(9600);                             // for debugging  
}

void loop() {
  // put your main code here, to run repeatedly:
  int push_val = digitalRead(push_button);

  if (old_push_val == HIGH && push_val == LOW) {
    mode++;
    mode%=3;
  }

  old_push_val = push_val;

  Serial.println(mode);

  delay(500);

}
