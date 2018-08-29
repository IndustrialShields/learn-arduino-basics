void setup() {
  Serial.begin(9600);
  pinMode(5, OUTPUT);
}

void loop() {
  turnOn();
  delay(1000);
  turnOff();
  delay(1000);
}

void turnOn() {
  Serial.println("Turn on...");
  digitalWrite(5, HIGH);
}

void turnOff(){
  Serial.println("Turn off...");
  digitalWrite(5, LOW);
}
