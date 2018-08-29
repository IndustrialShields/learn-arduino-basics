// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 5 as an output.
  Serial.begin(9600);
  pinMode(5, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  Serial.println("Turn on");
  digitalWrite(5, HIGH);   // turn the output on (HIGH is the voltage level)
  delay(1000);              // wait for a second

  Serial.println("Turn off");
  digitalWrite(5, LOW);    // turn the output off by making the voltage LOW
  delay(1000);              // wait for a second
}
