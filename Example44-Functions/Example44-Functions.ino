void setup() {
  Serial.begin(9600);
  pinMode(5, OUTPUT);
}

void loop() {
  digitalWrite(5, HIGH);
  turnOn();
  delay(1000);
  digitalWrite(5, LOW);
  turnOff();
  delay(1000);
}
