void setup() {
  // initialize digital pin 5 as an output.
  Serial.begin(9600);
  pinMode(5, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  int seconds = millis() / 1000;
  if (seconds % 2 == 0) {
    digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)
    Serial.println("1");
  }
  else {
    digitalWrite(5, LOW);    // turn the LED off by making the voltage LOW
    Serial.println("0");
  }
}
