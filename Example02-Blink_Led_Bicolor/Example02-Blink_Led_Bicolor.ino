// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pins 5 and 6 as outputs
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  Serial.println("Set GREEN");
  digitalWrite(5, HIGH);
  digitalWrite(6, LOW);
  delay(1000);              // wait for a second

  Serial.println("Set RED");
  digitalWrite(5, LOW);
  digitalWrite(6, HIGH);
  delay(1000);              // wait for a second

  Serial.println("Set ORANGE");
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  delay(1000);              // wait for a second

  Serial.println("Turn off");
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
  delay(1000);              // wait for a second
}
