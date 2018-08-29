// Only valid for direct Arduino pins

#define PIN_BUTTON 2
#define PIN_OUTPUT 3

void setup() {
  Serial.begin(9600);
  pinMode(PIN_BUTTON, INPUT_PULLUP);
  pinMode(PIN_OUTPUT, OUTPUT);
}

void loop() {
  int buttonValue = digitalRead(PIN_BUTTON);
  Serial.println(buttonValue);
  if (buttonValue == HIGH) {
    digitalWrite(PIN_OUTPUT, LOW);
  }
  else {
    digitalWrite(PIN_OUTPUT, HIGH);
  }
}
