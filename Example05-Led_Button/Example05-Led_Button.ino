int pushButton = 2;
int output = 5;

void setup() {
  Serial.begin(9600);
  pinMode(pushButton, INPUT);
  pinMode(output, OUTPUT);
}

void loop() {
  int buttonState = digitalRead(pushButton);
  Serial.println(buttonState);
  delay(1);

  if (buttonState == LOW) {
    digitalWrite(output, LOW);
    Serial.println("Turn off output");
  } else {
    digitalWrite(output, HIGH);
    Serial.println("Turn on output");
  }
}
