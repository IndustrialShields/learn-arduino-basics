#include "functions.h"

void setup() {
  Serial.begin(9600);
  pinMode(outputPin, OUTPUT);
}

void loop() {
  digitalWrite(outputPin, HIGH);
  turnOn();
  delay(1000);
  digitalWrite(outputPin, LOW);
  turnOff();
  delay(1000);
}
