// Only valid for direct Arduino pins

int lastButtonValue;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP); // button
  pinMode(5, OUTPUT);       // output
  lastButtonValue = digitalRead(2);
}

void loop() {
  int buttonValue = digitalRead(2);
  Serial.print(buttonValue);
  if (buttonValue != lastButtonValue) {
    // detect ascending edge
    if (buttonValue == HIGH) {
      // toggle output
      int outputValue = digitalRead(5);
      digitalWrite(5, !outputValue);
    }
  }
  Serial.print(" ");
  Serial.println(digitalRead(5));
  lastButtonValue = buttonValue;
}
