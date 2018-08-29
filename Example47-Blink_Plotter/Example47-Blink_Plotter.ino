void setup() {
  // initialize digital pin 5 as an output.
  Serial.begin(9600);
  pinMode(5, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(5, HIGH);   // turn the LED on (HIGH is the voltage level)
  Serial.println("1");
  delay(1000);              // wait for a second
  digitalWrite(5, LOW);    // turn the LED off by making the voltage LOW
  Serial.println("0");
  delay(1000);              // wait for a second
}
