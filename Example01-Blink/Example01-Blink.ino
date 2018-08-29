// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 5 as an output.
  pinMode(5, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(5, HIGH);   // turn the output on (HIGH is the voltage level)
  delay(1000);              // wait for a second (1000ms)
  digitalWrite(5, LOW);    // turn the output off by making the voltage LOW
  delay(1000);              // wait for a second (1000ms)
}
