int pinArray[] = {4, 5, 6};
int count = 0;
int timer = 100;

void setup() {
  // we make all the declarations at once
  for (count = 0; count < 3; count++) {
    pinMode(pinArray[count], OUTPUT);
  }
}

void loop() {
  for (count = 0; count < 3; count++) {
    digitalWrite(pinArray[count], HIGH);
    delay(timer);

    digitalWrite(pinArray[count], LOW);
    delay(timer);
  }

  for (count = 2; count >= 0; count--) {
    digitalWrite(pinArray[count], HIGH);
    delay(timer);

    digitalWrite(pinArray[count], LOW);
    delay(timer);
  }
}
